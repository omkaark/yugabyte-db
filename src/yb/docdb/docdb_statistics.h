// Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//

#pragma once

#include <memory>

namespace rocksdb {

class Statistics;
class ScopedStatistics;

} // namespace rocksdb

namespace yb::docdb {

class DocDBStatistics {
 public:
  DocDBStatistics();
  ~DocDBStatistics();

  rocksdb::Statistics* RegularDBStatistics() const;
  rocksdb::Statistics* IntentsDBStatistics() const;

  // TODO(hdr_histogram): used to forward histogram changes until histogram support is added to
  // this class.
  void SetHistogramContext(
      std::shared_ptr<rocksdb::Statistics> regulardb_statistics,
      std::shared_ptr<rocksdb::Statistics> intentsdb_statistics);

  void MergeAndClear(
      rocksdb::Statistics* regulardb_statistics,
      rocksdb::Statistics* intentsdb_statistics);

 private:
  std::unique_ptr<rocksdb::ScopedStatistics> regulardb_statistics_;
  std::unique_ptr<rocksdb::ScopedStatistics> intentsdb_statistics_;
};

} // namespace yb::docdb
