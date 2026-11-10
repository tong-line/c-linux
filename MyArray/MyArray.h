/*
 * MyArray.h - 纯 C 动态数组（vector）
 *
 * 用法示意：
 *     struct myarray a;
 *     myarray_init(&a, sizeof(int));
 *     int v = 42;
 *     myarray_push(&a, &v);
 *     int *p = myarray_at(&a, 0);
 *     myarray_free(&a);
 */
#ifndef MYARRAY_H
#define MYARRAY_H

#include <stddef.h>

/* 数组描述符：data 指向 cap * elem_size 字节的连续堆内存 */
struct myarray {
	void   *data;      /* TODO: 指向哪、什么时候重新分配？ */
	size_t  elem_size; /* 单个元素字节数 */
	size_t  len;       /* 已使用元素个数 */
	size_t  cap;       /* 已分配容量（元素个数，不是字节数） */
};

/* 便利宏：取长度 */
#define myarray_len(a) ((a)->len)

/* 内核同款，编译期求值 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/* 初始化：elem_size 必须 > 0 */
void myarray_init(struct myarray *a, size_t elem_size);

/* 释放堆内存，并把描述符复位 */
void myarray_free(struct myarray *a);

/* 保证至少能容纳 need 个元素（已有空间够就什么也不做） */
int myarray_reserve(struct myarray *a, size_t need);

/* 尾部追加一个元素 */
int myarray_push(struct myarray *a, const void *elem);

/* 尾部弹出；out 为 NULL 表示丢弃 */
int myarray_pop(struct myarray *a, void *out);

/* 取第 i 个元素，越界返回 NULL */
void *myarray_at(const struct myarray *a, size_t i);

/* 在下标 i 处插入，i 必须 <= len */
int myarray_insert(struct myarray *a, size_t i, const void *elem);

/* 删除下标 i 处的元素，i 必须 < len */
int myarray_remove(struct myarray *a, size_t i);

/* 清空元素但保留已分配内存 */
void myarray_clear(struct myarray *a);

#endif /* MYARRAY_H */
