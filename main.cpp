#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

//i - row
//j - column

struct matrix_elem_t {
    int32_t i, j, val;
};

struct matrix_t {
    //int32_t size;
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

int32_t set_matrix_elem(matrix_t *m, int32_t row, int32_t column, int32_t value)
{
    for (int32_t i = 0; i < m->elems.size(); i++) {
        if (m->elems[i].i == row && m->elems[i].j == column) {
            m->elems[i].val = value;
        }
    }
}

void print_matrix(struct matrix_t *m) 
{
    if (m == NULL)
        return;

    for (int i = 0; i < sqrt(m->elems.size()); i++)
        printf("~");
    printf("\n");

    for (int i = 1; i <= sqrt(m->elems.size()); i++) {
        for (int j = 1; j <= sqrt(m->elems.size()); j++) {
            printf("[%d] ", get_matrix_elem(m, i, j));
        }
        printf("\n");
    }

    for (int i = 0; i < sqrt(m->elems.size()); i++)
        printf("~");
    printf("\n");
}

matrix_t *delete_row_column(matrix_t *m, 
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
    if (m->elems.size() == 4) {
        return get_matrix_elem(m, 1, 1) * get_matrix_elem(m, 2, 2) -
               get_matrix_elem(m, 2, 1) * get_matrix_elem(m, 1, 2); 
    } else {
        int32_t ret = 0;
        
        for (uint32_t j = 1; j <= sqrt(m->elems.size()); j++) {
            matrix_t *tm = delete_row_column(m, 1, j);
            ret += (int32_t)pow(-1, 1 + j) * \
                   get_matrix_elem(m, 1, j) * matrix_det(tm);
            delete tm;
        }
        return ret;
    }
}

int32_t matrix_adjunct(matrix_t *m, int32_t i, int32_t j)
{
    matrix_t *mn = delete_row_column(m, i, j);
    int32_t adj =  (((i + j) % 2) ? -1 : 1) * matrix_det(mn);
    delete mn;
    return adj;
}

matrix_t *make_adj_matrix(matrix_t *m)
{
    matrix_t *madj = new matrix_t;
    for (int i = 1; i <= sqrt(m->elems.size()); i++) {
        for (int j = 1; j <= sqrt(m->elems.size()); j++) {
            matrix_elem_t elem;
            elem.val = matrix_adjunct(m, i, j);
            elem.i = i;
            elem.j = j;
            madj->elems.push_back(elem);
        }
    }
    return madj;
}

void transponse_matrix(matrix_t *m)
{
    for (int i = 1; i <= sqrt(m->elems.size()); i++) {
        for (int j = 1; j <= sqrt(m->elems.size()); j++) {
            if (j > i) {
                int32_t val_ij = get_matrix_elem(m, i, j);
                int32_t val_ji = get_matrix_elem(m, j, i);
                set_matrix_elem(m, i, j, val_ji);
                set_matrix_elem(m, j, i, val_ij);
            }
        }
    }
}

int32_t find_nok(matrix_t *m, int32_t det)
{
    int32_t nok = 0;
    std::vector<int32_t> arr;
    for (int32_t i = 0; i < m->elems.size(); i++) {
        arr.push_back((m->elems[i].val < 0) ? -m->elems[i].val : m->elems[i].val);
    }
    arr.push_back(det < 0 ? -det : det);
    
    //arr.push_back(75);
    //arr.push_back(25);
    //arr.push_back(15);
    //arr.push_back(100);

    int32_t max = arr[0];
    for (int32_t i = 1; i < arr.size(); i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    //std::vector<int>::iterator result;
    //result = std::max_element(arr.begin(), arr.end());
    for (int32_t i = 2; i < max;/*std::distance(arr.begin(), result);*/ i++) {
        int32_t count = 0;
        for (int j = 0; j < arr.size(); j++) {
            if ((arr[j] % i) == 0)
                count++;
            if (count == arr.size())
                nok = i;
        }
    }

    return nok;
}

void devide_matrix(matrix_t *m, int32_t div)
{
    for (int32_t i = 0; i < m->elems.size(); i++)
        m->elems[i].val /= div;
}

int main()
{
    matrix_t *m = new matrix_t;
    matrix_elem_t elem;

    elem.i = 1; elem.j = 1; elem.val = 0;
    m->elems.push_back(elem);
    elem.i = 1; elem.j = 2; elem.val = 8;
    m->elems.push_back(elem);
    elem.i = 1; elem.j = 3; elem.val = -8;
    m->elems.push_back(elem);
    elem.i = 1; elem.j = 4; elem.val = -2;
    m->elems.push_back(elem);
    elem.i = 1; elem.j = 5; elem.val = 7;
    m->elems.push_back(elem);

    elem.i = 2; elem.j = 1; elem.val = -3;
    m->elems.push_back(elem);
    elem.i = 2; elem.j = 2; elem.val =5;
    m->elems.push_back(elem);
    elem.i = 2; elem.j = 3; elem.val = 15;
    m->elems.push_back(elem);
    elem.i = 2; elem.j = 4; elem.val = 7;
    m->elems.push_back(elem);
    elem.i = 2; elem.j = 5; elem.val = 0;
    m->elems.push_back(elem);

    elem.i = 3; elem.j = 1; elem.val = 14;
    m->elems.push_back(elem);
    elem.i = 3; elem.j = 2; elem.val = 0;
    m->elems.push_back(elem);
    elem.i = 3; elem.j = 3; elem.val = 22;
    m->elems.push_back(elem);
    elem.i = 3; elem.j = 4; elem.val = 17;
    m->elems.push_back(elem);
    elem.i = 3; elem.j = 5; elem.val = 7;
    m->elems.push_back(elem);

    elem.i = 4; elem.j = 1; elem.val = 8;
    m->elems.push_back(elem);
    elem.i = 4; elem.j = 2; elem.val = 0;
    m->elems.push_back(elem);
    elem.i = 4; elem.j = 3; elem.val = 0;
    m->elems.push_back(elem);
    elem.i = 4; elem.j = 4; elem.val = -9;
    m->elems.push_back(elem);
    elem.i = 4; elem.j = 5; elem.val = 6;
    m->elems.push_back(elem);

    elem.i = 5; elem.j = 1; elem.val = 8;
    m->elems.push_back(elem);
    elem.i = 5; elem.j = 2; elem.val = 0;
    m->elems.push_back(elem);
    elem.i = 5; elem.j = 3; elem.val = 21;
    m->elems.push_back(elem);
    elem.i = 5; elem.j = 4; elem.val = -9;
    m->elems.push_back(elem);
    elem.i = 5; elem.j = 5; elem.val = 6;
    m->elems.push_back(elem);

    //m->size = 4;
    //print_matrix(m);
    //set_matrix_elem(m, 2, 2, 5000);
    //print_matrix(m);
    matrix_t *m_adj = make_adj_matrix(m);
    int32_t det_m = matrix_det(m);
    //print_matrix(m_adj);
    transponse_matrix(m_adj);
    //print_matrix(m_adj);

    //printf("det: %i\n", det_m);

    //matrix_t *mn = delete_row_column(m, 1, 1);
    //print_matrix(mn);
    //printf("det mn: %d\n", matrix_det(mn));

    //int32_t adj11 = matrix_adjunct(m, 1, 1);
    //printf("adj11: %d\n", adj11);
    int32_t nok = find_nok(m_adj, det_m);
    printf("nok: %d\n", nok);
    if (nok > 0) {
        if (det_m > 0) {
            det_m /= nok;
            devide_matrix(m_adj, nok);
        } else {
            det_m /= -nok;
            devide_matrix(m_adj, -nok);
        }
    } else {
        det_m /= -1;
        devide_matrix(m_adj, -1);
    }
    printf("det: %i\n", det_m);
    print_matrix(m_adj);

    delete m;
    delete m_adj;

    return 0;
}
