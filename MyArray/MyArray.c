/*
 * MyArray.c - 纯 C 动态数组实现（自己填）
 *
 * ============ 动手前先想清楚这几个问题 ============
 *
 * 1. 空数组 cap 初始值取多少？为什么不能是 0 直接 realloc？
 * 2. 扩容倍数取 2 还是 1.5？想想 n 次 push 的总拷贝量。
 * 3. 两个地方会整数溢出：cap 翻倍、"cap * elem_size"。
 *    size_t 回绕后是小值，怎么提前拦截？（提示：除法和 SIZE_MAX）
 * 4. void * 不能做算术。怎么按 i 取到第 i 个元素的地址？
 *    （提示：先转 char *）
 * 5. insert / remove 要搬移字节区间，源和目的重叠，
 *    该用 memcpy 还是 memmove？
 * 6. 失败怎么通知调用者？返回负数 errno，还是返回 NULL？
 *
 * 建议顺序：init/free → at → grow → push/pop → insert/remove
 * 每写完一个，用 main 里几行代码验证一次再往下。
 *
 * 编译（警告全开 + 内存检查）：
 *   gcc -std=c11 -Wall -Wextra -Wpedantic -g \
 *       -fsanitize=address,undefined -o test MyArray.c main.c
 *   ./test
 * ================================================
 */
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "MyArray.h"

/* 建议把扩容逻辑抽成一个 static 函数，push 和 insert 共用 */
#define MYARRAR_INIT_CAP 8;
int myarray_init(struct myarray *a, size_t elem_size)
{
    if (a == NULL || elem_size == 0) {
        return -1;
    }

    a->data = NULL;
    a->elem_size = elem_size;
    a->len = 0;
    a->cap = 0;
    return 0;
}

void myarray_free(struct myarray *a)
{
	free(a->data);
	a->data = NULL;
	a->len = 0;
	a->cap = 0;
}

int myarray_reserve(struct myarray *a, size_t need)
{
    if (a == NULL || a->elem_size == 0) {
        return -1;
    }
    if (need <= a->cap) {
        return 0;
    }
    if (need > SIZE_MAX / a->elem_size) {
        return -1;
    }
    size_t bytes = need * a->elem_size;
    void *p = realloc(a->data, bytes);
    if (p == NULL) {
        return -1;
    }
    a->data = p;
    a->cap = need;
	return 0;
}

int myarray_push(struct myarray *a, const void *elem)
{
	/* TODO: 先确保有空间，再拷贝，最后 len++（顺序错了会写出界） */
	return 0;
}

int myarray_pop(struct myarray *a, void *out)
{
	/* TODO: 空数组返回 -ENOENT */
	return 0;
}

void *myarray_at(const struct myarray *a, size_t i)
{
	/* TODO: 越界返回 NULL；注意 a 是 const，返回的是可写指针 */
	return NULL;
}

int myarray_insert(struct myarray *a, size_t i, const void *elem)
{
	/* TODO: i > len 返回 -EINVAL；先扩容，再后移，再写入 */
	return 0;
}

int myarray_remove(struct myarray *a, size_t i)
{
	/* TODO: i >= len 返回 -EINVAL */
	return 0;
}

void myarray_clear(struct myarray *a)
{
	/* TODO: 只改 len，不要 free */
}
