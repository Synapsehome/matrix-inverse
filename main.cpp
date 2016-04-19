#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <vector>
#include <cmath>

using namespace std;

//i - row
//j - column

struct matrix_elem_t {
    int32_t i, j, val;
};

struct matrix_t {
    int32_t size;
    std::vector<matrix_elem_t> elems;
};

int32_t get_matrix_elem(struct matrix_t *mat, 
                        int32_t i, int32_t j)
{
    int32_t count;
    for (count = 0; count < mat->elems.size(); count++) {
        if (mat->elems[count].i == i && 
                            mat->elems[count].j == j) {
            return mat->elems[count].val;
        }
    }

    return -1;
}

int32_t calc_matrix_det_without_i_j(struct matrix_t *m, 
        int32_t row, int32_t column)
{
    static int32_t det = 0;

    if (m->size == 2) {
        return get_matrix_elem(m, 1, 1) * get_matrix_elem(m, 2, 2) -
               get_matrix_elem(m, 2, 1) * get_matrix_elem(m, 1, 2);
    } else {
        matrix_t *tmp = (matrix_t *)malloc(m->elems.size() + 1);
    }
}

void print_matrix(struct matrix_t *m) 
{
    if (m == NULL)
        return;

    for (int i = 1; i <= sqrt(m->elems.size()); i++) {
        for (int j = 1; j <= sqrt(m->elems.size()); j++) {
            printf("%d ", get_matrix_elem(m, i, j));
        }
        printf("\n");
    }
}

matrix_t *delete_row_column(struct matrix_t *m, 
        int32_t row, int32_t column)
{
    int32_t count = 0;
    matrix_t *tm = new matrix_t;

    for (int32_t i = 0; i < m->elems.size(); i++) {
        tm->elems.push_back(m->elems[i]);
    }

    while (count < tm->elems.size()) {
        if (tm->elems[count].j == column || tm->elems[count].i == row) {
            tm->elems.erase(tm->elems.begin() + count);
            continue;
        }
        count++;
    }

    for (int i = 0; i < tm->elems.size(); i++) {
        if (tm->elems[i].i > row) {
            tm->elems[i].i -= 1;
        }
        
        if (tm->elems[i].j > column) {
            tm->elems[i].j -= 1;
        }
    }

    return tm;
}

int32_t matrix_det(matrix_t *m)
{
    static int32_t sum = 0;

    print_matrix(m);
    printf("\n");

    if (m->elems.size() == 4) {
        return get_matrix_elem(m, 1, 1) * get_matrix_elem(m, 2, 2) -
               get_matrix_elem(m, 2, 1) * get_matrix_elem(m, 1, 2); 
    } else {
        for (uint32_t j = 1; j <= sqrt(m->elems.size()); j++) {
            matrix_t *tm = delete_row_column(m, 1, j);
            sum += pow(-1, 1 + j) * get_matrix_elem(m, 1, j) * matrix_det(tm);
        }

        return sum;
    }
}

int main()
{
    matrix_t *m = new matrix_t;
    matrix_elem_t elem;

    elem.i = 1; elem.j = 1; elem.val = 5;
    m->elems.push_back(elem);
    elem.i = 1; elem.j = 2; elem.val = 5;
    m->elems.push_back(elem);
    elem.i = 1; elem.j = 3; elem.val = 5;
    m->elems.push_back(elem);
    elem.i = 1; elem.j = 4; elem.val = 5;
    m->elems.push_back(elem);

    elem.i = 2; elem.j = 1; elem.val = 2;
    m->elems.push_back(elem);
    elem.i = 2; elem.j = 2; elem.val = 0;
    m->elems.push_back(elem);
    elem.i = 2; elem.j = 3; elem.val = 5;
    m->elems.push_back(elem);
    elem.i = 2; elem.j = 4; elem.val = 7;
    m->elems.push_back(elem);

    elem.i = 3; elem.j = 1; elem.val = 0;
    m->elems.push_back(elem);
    elem.i = 3; elem.j = 2; elem.val = 4;
    m->elems.push_back(elem);
    elem.i = 3; elem.j = 3; elem.val = 0;
    m->elems.push_back(elem);
    elem.i = 3; elem.j = 4; elem.val = 0;
    m->elems.push_back(elem);

    elem.i = 4; elem.j = 1; elem.val = 0;
    m->elems.push_back(elem);
    elem.i = 4; elem.j = 2; elem.val = 0;
    m->elems.push_back(elem);
    elem.i = 4; elem.j = 3; elem.val = 6;
    m->elems.push_back(elem);
    elem.i = 4; elem.j = 4; elem.val = 0;
    m->elems.push_back(elem);

    m->size = 4;

    /*print_matrix(m);

    matrix_t *tm = delete_row_column(m, 2, 3);

    printf("\n");
    print_matrix(tm);

    tm->size = 4;
*/
    printf("det: %i\n", matrix_det(m));

   return 0;
}
