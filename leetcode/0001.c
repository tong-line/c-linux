
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TABLE_SIZE 1024

// 哈希表节点
typedef struct HashEntry {
    int key;                    // 数字
    int value;                  // 数组下标
    struct HashEntry *next;     // 下一个节点
} HashEntry;

// 哈希表
typedef struct {
    HashEntry *buckets[TABLE_SIZE];
} HashMap;

// 哈希函数
static size_t hash(int key)
{
    return (size_t)(uint32_t)key % TABLE_SIZE;
}

// 查找 key，找到返回节点，找不到返回 NULL
static HashEntry *hash_find(HashMap *map, int key)
{
    size_t index = hash(key);

    HashEntry *cur = map->buckets[index];

    while (cur != NULL) {
        if (cur->key == key)
            return cur;

        cur = cur->next;
    }

    return NULL;
}

// 插入 key-value
static int hash_insert(HashMap *map, int key, int value)
{
    HashEntry *entry = malloc(sizeof(*entry));

    if (entry == NULL)
        return -1;

    entry->key = key;
    entry->value = value;

    size_t index = hash(key);

    // 头插法
    entry->next = map->buckets[index];
    map->buckets[index] = entry;

    return 0;
}

// 销毁哈希表
static void hash_destroy(HashMap *map)
{
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        HashEntry *cur = map->buckets[i];

        while (cur != NULL) {
            HashEntry *next = cur->next;
            free(cur);
            cur = next;
        }

        map->buckets[i] = NULL;
    }
}

// Two Sum
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    if (returnSize == NULL)
        return NULL;

    *returnSize = 0;

    if (nums == NULL || numsSize < 2)
        return NULL;

    HashMap map = {0};

    for (int j = 0; j < numsSize; j++) {

        // 计算需要寻找的另一个数字
        int complement = target - nums[j];

        // 在哈希表中查找
        HashEntry *entry = hash_find(&map, complement);

        if (entry != NULL) {

            int *ans = malloc(2 * sizeof(*ans));

            if (ans == NULL) {
                hash_destroy(&map);
                return NULL;
            }

            ans[0] = entry->value;
            ans[1] = j;

            *returnSize = 2;

            hash_destroy(&map);

            return ans;
        }

        // 没找到，把当前数字存进去
        if (hash_insert(&map, nums[j], j) != 0) {
            hash_destroy(&map);
            return NULL;
        }
    }

    hash_destroy(&map);

    return NULL;
}

int main(void)
{
    int nums[] = {1,1,1,2,3,4,6,2, 7, 11, 15};
    int returnSize = 0;

    int *ans = twoSum(nums, 4, 9, &returnSize);

    if (ans != NULL) {
        printf("[%d, %d]\n", ans[0], ans[1]);
        free(ans);
    }

    return 0;
}
