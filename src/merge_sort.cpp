// (c) 2020 Jim Stockwell
// This code is licensed under MIT license
// (see http://opensource.org/licenses/MIT for details)

#include <string>
#include <future>
#include <cstdlib>
using namespace std;

/* result is where the merged 'a' and 'b' go.
 * result can accept at least 'len' ints
 * a is of length (len/2)
 * b is of length (len - len/2)
 * Note: a and b are not equal length when 'len' is odd.
 */
static void merge(
    int *const result,
    const size_t len,
    const int *const a,
    const int *const b)
{
    const int alen = len / 2;
    const int blen = len - len / 2;

    for (int ai = 0, bi = 0, ri = 0; ri < len;)
    {
        /* At this point,
         * ai and bi both indicate an unmerged value.
         * When a or b has no more unmerged values,
         * ai or bi will be equal to alen or blen respectively.
         */
        if (ai < alen && bi < blen)
        {
            if (a[ai] < b[bi])
            {
                result[ri++] = a[ai++];
            }
            else
            {
                result[ri++] = b[bi++];
            }
        }
        else if (ai < alen)
        {
            result[ri++] = a[ai++];
        }
        else
        {
            result[ri++] = b[bi++];
        }
    }
}

int *merge_sort(int *const data, const size_t len)
{
    if (len < 2)
        return (data);

    int * const a = (int *)malloc((len / 2) * sizeof(int));
    int * const b = (int *)malloc((len - len / 2) * sizeof(int));

    memcpy(a, data, len / 2 * sizeof(int));
    memcpy(b, data + len / 2, (len - len / 2) * sizeof(int));

    if (len < 500)
    {
        merge_sort(a, len / 2);
        merge_sort(b, len - len / 2);
        merge(data, len, a, b);
    }
    else
    {
        future<int *> future_a = async(std::launch::async, merge_sort, a, len / 2);
        future<int *> future_b = async(std::launch::async, merge_sort, b, len - len / 2);
        merge(data, len, future_a.get(), future_b.get());
    }

    free(b);
    free(a);

    return (data);
}
