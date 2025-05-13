
#include "xenia/f2/features.h"

namespace xe {
namespace f2 {
/* Accesses to this data could theoretically race--but in practice they won't.
 */
SaveFileBackupState<7> active_save_file_backup = {
    /* The code responsible for backing up the save files, in
       `NtCreateFile_entry`, relies on each of these paths beginning with a
       prefix of 'save:\'. */
    {"save:\\chaptersave.bin", "save:\\Fable2PubInfo.xml",
     "save:\\failquestsave.bin", "save:\\herosave.bin", "save:\\mainsave.bin",
     "save:\\saveuid.bin", "save:\\texturemorphs.bin"}};
}  // namespace f2
}  // namespace xe
