#include "../../include/infinite-number.h"

ifNumber *ifNumber_create(void)
{
    ifNumber *nb = NULL;

    nb = malloc(sizeof(ifNumber));
    if (nb == NULL)
        return NULL;
    nb->digit = 0;
    nb->next = NULL;
    return nb;
}

void ifNumber_destroy(ifNumber *nb)
{
    if (nb == NULL)
        return;
    ifNumber_destroy(nb->next);
    return free(nb);
}

void ifNumber_display(ifNumber *nb)
{
    unsigned char digit;

    if (nb == NULL)
        return;
    ifNumber_display(nb->next);
    digit = nb->digit + '0';
    write(1, &digit, 1);
    return;
}

ifNumber *ifNumber_set_number(ifNumber *nb, unsigned long val)
{
    unsigned char digit = 0;

    if (val == 0) {
        ifNumber_destroy(nb);
        return NULL;
    }
    if (nb == NULL)
        nb = ifNumber_create();
    if (nb == NULL)
        return NULL;
    digit = val % 10;
    nb->digit = digit;
    nb->next = ifNumber_set_number(nb->next, val / 10);
    if (nb->next == NULL && val / 10 != 0) {
        free(nb);
        return NULL;
    }
    return nb;
}

static ifNumber *ifNumber_add_with_carry(ifNumber *nb, ifNumber *add,
    unsigned char carry)
{
    ifNumber *res = NULL;
    int new_carry = 0;

    if (nb == NULL && add == NULL && carry == 0)
        return NULL;
    res = ifNumber_create();
    if (res == NULL)
        return NULL;
    if (nb != NULL)
        res->digit += nb->digit;
    if (add != NULL)
        res->digit += add->digit;
    res->digit += carry;
    new_carry = res->digit - 9;
    res->digit %= 10;
    if (new_carry > 0)
        new_carry = new_carry / 10 + 1;
    else
        new_carry = 0;
    res->next = ifNumber_add_with_carry(nb == NULL ? NULL : nb->next, add == NULL ? NULL : add->next, new_carry);
    if (res->next == NULL && ((nb != NULL && nb->next != NULL) || (add != NULL && add->next != NULL) || carry != 0)) {
        free(res);
        return NULL;
    }
    return res;
}

ifNumber *ifNumber_add(ifNumber *nb, ifNumber *add)
{
    return ifNumber_add_with_carry(nb, add, 0);
}
