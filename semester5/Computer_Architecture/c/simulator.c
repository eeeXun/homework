#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define KB (1 << 10)
#define MAX ((unsigned)(-1) >> 1)

typedef struct {
    int valid;
    int tag;
    int hist;
} CACHE_ROW;

typedef struct {
    // config
    int tag_size, index_size, offest_size, way, num_rows;
    // data
    CACHE_ROW* row;
    int* row_hist;
} CACHE;

void init_cache(CACHE* cache);
void print_config(CACHE cache);
void trace(CACHE* cache, int LRU);

int main(int argc, char** argv)
{
    CACHE cache;
    init_cache(&cache);
    print_config(cache);
    // trace
    if (argv[1][0] == '0')
        trace(&cache, 0); // FIFO
    else
        trace(&cache, 1); // LRU

    return 0;
}

void init_cache(CACHE* cache)
{
    char buf[20];
    int machine_bit, cache_size, way, block_size;
    scanf("%s %s %d", buf, buf, &machine_bit);
    scanf("%s %s %d", buf, buf, &cache_size);
    cache_size *= KB;
    scanf("%s %d", buf, &way);
    scanf("%s %s %d", buf, buf, &block_size);
    // init cache
    cache->offest_size = log2(block_size);
    cache->index_size = log2(cache_size / (block_size * way));
    cache->tag_size = machine_bit - cache->offest_size - cache->index_size;
    cache->way = way;
    cache->num_rows = (int)pow(2, cache->index_size);
    cache->row
        = (CACHE_ROW*)calloc(cache->num_rows * cache->way, sizeof(CACHE_ROW));
    cache->row_hist = (int*)calloc(cache->num_rows * cache->way, sizeof(int));
}

void print_config(CACHE cache)
{
    printf("num_set: %d\n", cache.num_rows);
    printf("num_block_offset_bit: %d\n", cache.offest_size);
    printf("num_index_bit: %d\n", cache.index_size);
    printf("num_tag_bit: %d\n", cache.tag_size);
}

void trace(CACHE* cache, int LRU)
{
    int times = 0, hit_times = 0, miss_times = 0;
    char buf1, buf2;
    int addr;
    int min_set, min_hist;
    int tmp, tmp_tag, tmp_row;
    int hit, find_empty;
    printf("\nhit trace:\n\n");
    // start
    scanf(" %c %c", &buf1, &buf2);
    while (scanf("%x", &addr) == 1) {
        min_set = 0;
        min_hist = MAX;
        hit = 0;
        find_empty = 0;
        times++;
        tmp = (addr >> cache->offest_size);
        tmp_row = (tmp % cache->num_rows);
        tmp_tag = (tmp >> cache->index_size);
        for (int i = 0; i < cache->way; i++) {
            if (cache->row[tmp_row * cache->way + i].valid
                && cache->row[tmp_row * cache->way + i].tag == tmp_tag) {
                hit = 1;
                hit_times++;
                cache->row_hist[tmp_row]++;
                if (LRU)
                    cache->row[tmp_row * cache->way + i].hist
                        = cache->row_hist[tmp_row];
                printf("%c: %.5x hit set: 0x%x way: 0x%x\n", buf1, addr,
                    tmp_row, i);
                break;
            } else if (cache->row[tmp_row * cache->way + i].valid
                && cache->row[tmp_row * cache->way + i].tag != tmp_tag
                && cache->row[tmp_row * cache->way + i].hist < min_hist
                && !find_empty) {
                min_set = i;
                min_hist = cache->row[tmp_row * cache->way + i].hist;
            } else if (!cache->row[tmp_row * cache->way + i].valid
                && !find_empty) {
                find_empty = 1;
                min_set = i;
            }
        }
        if (!hit) {
            miss_times++;
            if (find_empty)
                cache->row[tmp_row * cache->way + min_set].valid = 1;
            cache->row_hist[tmp_row]++;
            cache->row[tmp_row * cache->way + min_set].hist
                = cache->row_hist[tmp_row];
            cache->row[tmp_row * cache->way + min_set].tag = tmp_tag;
        }
        scanf(" %c %c", &buf1, &buf2);
    }
    // end
    printf("\n");
    printf("num_total_access: %d\n", times);
    printf("num_hit: %d\n", hit_times);
    printf("num_miss: %d\n", miss_times);
    printf("hit_rate: %.2lf%%\n", ((double)hit_times / times) * 100);
}
