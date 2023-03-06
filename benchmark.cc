#include <algorithm>
#include <memory>
#include <string_view>

#include "benchmark/benchmark.h"
#include "blosc.h"
#include "external/bitshuffle/src/bitshuffle.h"
#include "lz4.h"
#include "lz4hc.h"
#include "zstd.h"

using namespace std::literals;

namespace {
constexpr std::string_view text =
    R"(These are short, famous texts in English from classic sources like the Bible or Shakespeare. Some texts have word definitions and explanations to help you. Some of these texts are written in an old style of English. Try to understand them, because the English that we speak today is based on what our great, great, great, great grandparents spoke before! Of course, not all these texts were originally written in English. The Bible, for example, is a translation. But they are all well known in English today, and many of them express beautiful thoughts.)";
constexpr std::string_view sql =
    R"xyz(SELECT
  e.employee_id AS "Employee #"
  , e.first_name || ' ' || e.last_name AS "Name"
  , e.email AS "Email"
  , e.phone_number AS "Phone"
  , TO_CHAR(e.hire_date, 'MM/DD/YYYY') AS "Hire Date"
  , TO_CHAR(e.salary, 'L99G999D99', 'NLS_NUMERIC_CHARACTERS = ''.,'' NLS_CURRENCY = ''$''') AS "Salary"
  , e.commission_pct AS "Comission %"
  , 'works as ' || j.job_title || ' in ' || d.department_name || ' department (manager: '
    || dm.first_name || ' ' || dm.last_name || ') and immediate supervisor: ' || m.first_name || ' ' || m.last_name AS "Current Job"
  , TO_CHAR(j.min_salary, 'L99G999D99', 'NLS_NUMERIC_CHARACTERS = ''.,'' NLS_CURRENCY = ''$''') || ' - ' ||
      TO_CHAR(j.max_salary, 'L99G999D99', 'NLS_NUMERIC_CHARACTERS = ''.,'' NLS_CURRENCY = ''$''') AS "Current Salary"
  , l.street_address || ', ' || l.postal_code || ', ' || l.city || ', ' || l.state_province || ', '
    || c.country_name || ' (' || r.region_name || ')' AS "Location"
  , jh.job_id AS "History Job ID"
  , 'worked from ' || TO_CHAR(jh.start_date, 'MM/DD/YYYY') || ' to ' || TO_CHAR(jh.end_date, 'MM/DD/YYYY') ||
    ' as ' || jj.job_title || ' in ' || dd.department_name || ' department' AS "History Job Title"
  
FROM employees e
-- to get title of current job_id
  JOIN jobs j 
    ON e.job_id = j.job_id
-- to get name of current manager_id
  LEFT JOIN employees m 
    ON e.manager_id = m.employee_id
-- to get name of current department_id
  LEFT JOIN departments d 
    ON d.department_id = e.department_id
-- to get name of manager of current department
-- (not equal to current manager and can be equal to the employee itself)
  LEFT JOIN employees dm 
    ON d.manager_id = dm.employee_id
-- to get name of location
  LEFT JOIN locations l
    ON d.location_id = l.location_id
  LEFT JOIN countries c
    ON l.country_id = c.country_id
  LEFT JOIN regions r
    ON c.region_id = r.region_id
-- to get job history of employee
  LEFT JOIN job_history jh
    ON e.employee_id = jh.employee_id
-- to get title of job history job_id
  LEFT JOIN jobs jj
    ON jj.job_id = jh.job_id
-- to get namee of department from job history
  LEFT JOIN departments dd
    ON dd.department_id = jh.department_id

ORDER BY e.employee_id;)xyz";
constexpr size_t dst_sz = 1048576;
} // namespace

namespace shrinkstring {
class ContextDeleter {
public:
  void operator()(ZSTD_CCtx *cctx) { ZSTD_freeCCtx(cctx); }
};

static void BM_Zstd(benchmark::State &state, std::string_view input) {
  std::unique_ptr<char[]> dst(new char[dst_sz]);
  std::unique_ptr<ZSTD_CCtx, ContextDeleter> cctx(ZSTD_createCCtx());
  size_t out{0};
  size_t in{0};
  for (auto _ : state) {
    out += ZSTD_compressCCtx(cctx.get(), dst.get(), dst_sz, input.data(),
                             input.size(), state.range(0));
    in += input.size();
  }
  state.counters["in"] = in;
  state.counters["out"] = out;
  state.counters["ratio"] = 1. * in / out;
  state.SetBytesProcessed(uint64_t(state.iterations()) * uint64_t(input.size()));
}

BENCHMARK_CAPTURE(BM_Zstd, text, text)->Arg(1);
BENCHMARK_CAPTURE(BM_Zstd, sql, sql)->Arg(1);
/*
static void BM_LZ4HC(benchmark::State &state, std::string_view input) {
  std::unique_ptr<char[]> dst(new char[dst_sz]);
  size_t out{0};
  size_t in{0};
  for (auto _ : state) {
    out += LZ4_compress_HC(input.data(), dst.get(), input.size(), dst_sz,
                           state.range(0));
    in += input.size();
  }
  state.counters["in"] = in;
  state.counters["out"] = out;
  state.counters["ratio"] = 1. * in / out;
  state.SetBytesProcessed(uint64_t(state.iterations()) * uint64_t(input.size()));
}

BENCHMARK_CAPTURE(BM_LZ4HC, text, text)->DenseRange(3, 12, 1);
BENCHMARK_CAPTURE(BM_LZ4HC, sql, sql)->DenseRange(3, 12, 1);
*/
static void BM_LZ4Fast(benchmark::State &state, std::string_view input) {
  std::unique_ptr<char[]> dst(new char[dst_sz]);
  size_t out{0};
  size_t in{0};
  for (auto _ : state) {
    out += LZ4_compress_fast(input.data(), dst.get(), input.size(), dst_sz,
                             state.range(0));
    in += input.size();
  }
  state.counters["in"] = in;
  state.counters["out"] = out;
  state.counters["ratio"] = 1. * in / out;
  state.SetBytesProcessed(uint64_t(state.iterations()) * uint64_t(input.size()));
}

BENCHMARK_CAPTURE(BM_LZ4Fast, text, text)->DenseRange(1, 20, 1);
BENCHMARK_CAPTURE(BM_LZ4Fast, sql, sql)->DenseRange(1, 20, 1);
/*
static void BM_BshufLZ4(benchmark::State &state) {
  std::unique_ptr<char[]> dst(new char[dst_sz]);
  size_t out{0};
  size_t in{0};
  for (auto _ : state) {
    out += bshuf_compress_lz4(input.data(), dst.get(), input.size(), 1, 0);
    in += input.size();
  }
  state.counters["in"] = in;
  state.counters["out"] = out;
  state.counters["ratio"] = 1. * in / out;
  state.SetBytesProcessed(uint64_t(state.iterations()) * uint64_t(input.size()));
}

BENCHMARK(BM_BshufLZ4);

static void BM_BshufZstd(benchmark::State &state) {
  std::unique_ptr<char[]> dst(new char[dst_sz]);
  size_t out{0};
  size_t in{0};
  for (auto _ : state) {
    out += bshuf_compress_zstd(input.data(), dst.get(), input.size(), 1, 0,
                               state.range(0));
    in += input.size();
  }
  state.counters["in"] = in;
  state.counters["out"] = out;
  state.counters["ratio"] = 1. * in / out;
  state.SetBytesProcessed(uint64_t(state.iterations()) * uint64_t(input.size()));
}

BENCHMARK(BM_BshufZstd)->DenseRange(0, 2, 1);

static void BM_BloscLZ4(benchmark::State &state) {
  blosc_init();
  blosc_set_compressor("lz4");
  std::unique_ptr<char[]> dst(new char[dst_sz]);
  size_t out{0};
  size_t in{0};
  for (auto _ : state) {
    out += blosc_compress(state.range(0), BLOSC_BITSHUFFLE, 1, input.size(),
                          input.data(), dst.get(), dst_sz);
    in += input.size();
  }
  state.counters["in"] = in;
  state.counters["out"] = out;
  state.counters["ratio"] = 1. * in / out;
  state.SetBytesProcessed(uint64_t(state.iterations()) * uint64_t(input.size()));
}

BENCHMARK(BM_BloscLZ4)->DenseRange(0, 9, 1);
*/
} // namespace shrinkstring

BENCHMARK_MAIN();