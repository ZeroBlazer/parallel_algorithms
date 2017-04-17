#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void linked_list_operations(size_t thrd_cnt);

void* operations(void* rank);

int Member(int value);

int Insert(int value);

int Delete(int value);