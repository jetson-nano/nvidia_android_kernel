#!/bin/sh

# Runs many iterations of run_net_test.sh in parallel processes, for the
# purposes of finding flaky tests.

if ! [[ $1 =~ ^[0-9]+$ ]] || ! [[ $2 =~ ^[0-9]+$ ]]; then
  echo "Usage: $0 <workers> <runs_per_worker>" >&2
  exit 1
fi

# A function run by every worker. Runs the tests <runs_per_worker> times.
function runtests() {
  local worker=$1
  local runs=$2
  local j=0
  while ((j < runs)); do
    $DIR/run_net_test.sh --readonly --builder --nobuild all_tests.sh \
        > /dev/null 2> $RESULTSDIR/results.$worker.$j
    j=$((j + 1))
    echo -n "." >&2
  done
}

WORKERS=$1
RUNS=$2
DIR=$(dirname $0)
RESULTSDIR=$(mktemp --tmpdir -d net_test.parallel.XXXXXX)
[ -z $RESULTSDIR ] && exit 1

echo "Building kernel..." >&2
$DIR/run_net_test.sh --norun

echo "Running $WORKERS worker(s) with $RUNS test run(s) each..." >&2

# Start all the workers.
worker=0
while ((worker < WORKERS)); do
  runtests $worker $RUNS &
  worker=$((worker + 1))
done
wait

echo

# Output the results.
egrep -h "^ERROR:|^FAIL:|0 failed tests|giving up" $RESULTSDIR/results.* | \
    sort | uniq -c | sort -rn >&2

# If there were any failures, leave the results around for examination.
if egrep -q "^ERROR|^FAIL" $RESULTSDIR/results.*; then
  echo "Failures occurred, leaving results in $RESULTSDIR" >&2
else
  rm -rf $RESULTSDIR
fi
