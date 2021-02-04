#!/usr/bin/env bash
set -Eeuxo pipefail

DOC_ARTIFACTS="/tmp/artifacts/log"

cd 

git config --global user.email "himanshupillai@gmail.com"
git config --global user.name "him-28"


# Clone the docs repository
git clone --depth 1 git@github.com:esmf-org/esmf-test-artifacts.git

# Test coverage -------------------------------------------------------------------

cd esmf-test-artifacts
mkdir test_coverage

cd ${DOC_ARTIFACTS}
cp -rf ESMF_* ~/esmf-test-artifacts/test_coverage/
cp -rf ESMC_* ~/esmf-test-artifacts/test_coverage/
cp -rf Methods_Tests ~/esmf-test-artifacts/test_coverage/ 

cd ~/esmf-test-artifacts/
git add .
git commit -a -m " Test Coverage pushed in the artifacts `date` "

# Push the changes ------------------------------------------------------------

git remote prune origin
git push origin master
