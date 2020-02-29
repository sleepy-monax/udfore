#include "udfore/utils/List.h"
#include "udfore/utils/Utils.h"

List *list_create(void)
{
    List *this = __create(List);

    this->count = 0;
    this->head = NULL;
    this->tail = NULL;

    return this;
}

void list_destroy(List *list) { list_destroy_with_callback(list, NULL); }
void list_destroy_with_callback(List *list, ListDestroyElementCallback callback)
{
    list_clear_with_callback(list, callback);
    free(list);
}

void list_clear(List *list) { list_clear_with_callback(list, NULL); }
void list_clear_with_callback(List *list, ListDestroyElementCallback callback)
{
    ListItem *current = list->head;

    while (current)
    {
        ListItem *next = current->next;

        if (callback)
        {
            callback(current->value);
        }

        free(current);

        current = next;
    }

    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
}

List *list_clone(List *this)
{
    List *copy = list_create();

    list_foreach(void, value, this)
    {
        list_pushback(copy, value);
    }

    return copy;
}

void list_insert_sorted(List *this, void *value, ListCompareElementCallback callback)
{
    if (this->head == NULL || callback(value, this->head->value))
    {
        list_push(this, value);
    }
    else
    {
        ListItem *current = this->head;

        while (current->next != NULL && callback(current->next->value, value))
        {
            current = current->next;
        }

        ListItem *item = malloc(sizeof(ListItem));

        item->prev = current;
        item->next = current->next;
        item->value = value;

        if (current->next == NULL)
        {
            this->tail = item;
        }
        else
        {
            current->next->prev = item;
        }

        current->next = item;

        this->count++;
    }
}

bool list_peek(List *this, void **value)
{
    if (this->head != NULL)
    {
        *value = this->head->value;

        return true;
    }
    else
    {
        *value = NULL;

        return false;
    }
}

bool list_peekback(List *this, void **value)
{
    if (this->tail != NULL)
    {
        *value = this->tail->value;

        return true;
    }
    else
    {
        return false;
    }
}

static void list_peekat_from_head(List *this, int index, void **value)
{
    ListItem *current = this->head;

    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    *value = current->value;
}

static void list_peekat_from_back(List *this, int index, void **value)
{
    ListItem *current = this->tail;

    for (int i = 0; i < (this->count - index - 1); i++)
    {
        current = current->prev;
    }

    *value = current->value;
}

bool list_peekat(List *this, int index, void **value)
{
    if (this->count >= 1 && index >= 0 && index < this->count)
    {
        if (index < this->count / 2)
        {
            list_peekat_from_head(this, index, value);
        }
        else
        {
            list_peekat_from_back(this, index, value);
        }

        return true;
    }
    else
    {
        return false;
    }
}

int list_indexof(List *this, void *value)
{
    int index = 0;

    list_foreach(void, item, this)
    {
        if (item == value)
        {
            return index;
        }

        index++;
    }

    return -1;
}

void list_push(List *this, void *value)
{
    ListItem *item = malloc(sizeof(ListItem));

    item->prev = NULL;
    item->next = NULL;
    item->value = value;

    this->count++;

    if (this->head == NULL)
    {
        this->head = item;
        this->tail = item;
    }
    else
    {
        this->head->prev = item;
        item->next = this->head;
        this->head = item;
    }
}

bool list_pop(List *this, void **value)
{
    ListItem *item = this->head;

    if (this->count == 0)
    {
        return false;
    }
    else if (this->count == 1)
    {
        this->count = 0;
        this->head = NULL;
        this->tail = NULL;
    }
    else if (this->count > 1)
    {
        item->next->prev = NULL;
        this->head = item->next;

        this->count--;
    }

    if (value != NULL)
    {
        *value = item->value;
    }

    return true;
}

void list_pushback(List *this, void *value)
{
    ListItem *item = malloc(sizeof(ListItem));

    item->prev = NULL;
    item->next = NULL;
    item->value = value;

    this->count++;

    if (this->tail == NULL)
    {
        this->tail = item;
        this->head = item;
    }
    else
    {
        this->tail->next = item;
        item->prev = this->tail;
        this->tail = item;
    }
}

bool list_popback(List *this, void **value)
{
    ListItem *item = this->tail;

    if (this->count == 0)
    {
        return NULL;
    }
    else if (this->count == 1)
    {
        this->count = 0;
        this->head = NULL;
        this->tail = NULL;
    }
    else if (this->count > 1)
    {
        item->prev->next = NULL;
        this->tail = item->prev;

        this->count--;
    }

    if (value != NULL)
    {
        *value = item->value;
    }

    return true;
}

bool list_remove(List *this, void *value)
{
    for (ListItem *item = this->head; item != NULL; item = item->next)
    {
        if (item->value == value)
        {
            if (item->prev != NULL)
            {
                item->prev->next = item->next;
            }
            else
            {
                this->head = item->next;
            }

            if (item->next != NULL)
            {
                item->next->prev = item->prev;
            }
            else
            {
                this->tail = item->prev;
            }

            this->count--;
            free(item);

            return true;
        }
    }

    return false;
}

bool list_contains(List *this, void *value)
{
    list_foreach(void, item, this)
    {
        if (item == value)
        {
            return true;
        }
    }

    return false;
}