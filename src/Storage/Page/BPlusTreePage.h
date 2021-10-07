//
// Created by 何智强 on 2021/10/5.
//

#ifndef MINIKV_BPLUSTREEPAGE_H
#define MINIKV_BPLUSTREEPAGE_H

#include <cassert>
#include <climits>
#include <cstdlib>
#include <string>

#include "src/Common/Config.h"
#include "src/Storage/BufferPool/BufferPoolManager.h"
#include "src/Concurrency/Transaction.h"

namespace miniKV {

#define MappingType std::pair<KeyType, ValueType>

// define page type enum

enum class IndexPageType { INVALID_INDEX_PAGE = 0, LEAF_PAGE, INTERNAL_PAGE };

#define INDEX_TEMPLATE_ARGUMENTS template <typename KeyType, typename ValueType>


/**
 * Both internal and leaf page are inherited from this page.
 *
 * It actually serves as a header part for each B+ tree page and
 * contains information shared by both leaf page and internal page.
 *
 * Header format (size in byte, 20 bytes in total):
 * ----------------------------------------------------------------------------
 * | PageType (4) | CurrentSize (4) | MaxSize (4) |
 * ----------------------------------------------------------------------------
 * | ParentPageId (4) | PageId(4) |
 * ----------------------------------------------------------------------------
 */
class BPlusTreePage {
public:
    bool IsLeafPage() const;
    bool IsRootPage() const;
    void SetPageType(IndexPageType page_type);

    int GetSize() const;
    void SetSize(int size);
    void IncreaseSize(int amount);

    int GetMaxSize() const;
    void SetMaxSize(int max_size);
    int GetMinSize() const;

    page_id_t GetParentPageId() const;
    void SetParentPageId(page_id_t parent_page_id);

    page_id_t GetPageId() const;
    void SetPageId(page_id_t page_id);

private:
    // member variable, attributes that both internal and leaf page share
    IndexPageType page_type_ __attribute__((__unused__));
    int size_ __attribute__((__unused__));
    int max_size_ __attribute__((__unused__));
    page_id_t parent_page_id_ __attribute__((__unused__));
    page_id_t page_id_ __attribute__((__unused__));
};

}



#endif //MINIKV_BPLUSTREEPAGE_H