
#ifndef XENIA_F2_FEATURES_H_
#define XENIA_F2_FEATURES_H_

#include <array>
#include <string>
#include <vector>

namespace xe {
namespace f2 {
template <size_t eligible_file_count>
struct SaveFileBackupState {
  std::array<std::string, eligible_file_count> eligible_file_paths;
  std::array<std::vector<uint8_t>, eligible_file_count> file_contents;
};

/* Accesses to this data could theoretically race--but in practice they won't.
 */
extern SaveFileBackupState<7> active_save_file_backup;
}  // namespace f2
}  // namespace xe

#endif  // XENIA_F2_FEATURES_H_
