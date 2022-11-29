#include "queue.h"
#include "dll.h"
#include "music_player.h"
#include <stdio.h>
#include <stdlib.h>

playlist_t *create_playlist() // return a newly created doubly linked list
{
    // DO NOT MODIFY!!!
    playlist_t *playlist = (playlist_t *)malloc(sizeof(playlist));
    playlist->list = create_list();
    playlist->num_songs = 0;
    playlist->last_song = NULL;
    return playlist;
}

void delete_playlist(playlist_t *playlist) // delete the playlist
{
    // DO NOT MODIFY!!!
    delete_list(playlist->list);
    free(playlist);
}

music_queue_t *create_music_queue() // return a newly created queue
{
    // DO NOT MODIFY!!!
    return create_queue();
}

void clear_music_queue(music_queue_t *q) // clear the queue q
{
    // DO NOT MODIFY!!!
    delete_queue(q);
}

void add_song(playlist_t *playlist, int song_id, int where) // TODO: add a song id to the end of the playlist
{
    if (where == -1)
        insert_front(playlist->list, song_id);

    else if (where == -2)
        insert_back(playlist->list, song_id);

    if (where > 0)
        insert_after(playlist->list, song_id, where);

	playlist->num_songs = playlist->list->size;
}

void delete_song(playlist_t *playlist, int song_id) // TODO: remove song id from the playlist
{
    delete_node(playlist->list, song_id);
}

song_t *search_song(playlist_t *playlist, int song_id) // TODO: return a pointer to the node where the song id is present in the playlist
{
    return search(playlist->list, song_id);
}

void search_and_play(playlist_t *playlist, int song_id) // TODO: play the song with given song_id from the list(no need to bother about the queue. Call to this function should always play the given song and further calls to play_next and play_previous)
{
    song_t *song = search_song(playlist, song_id);
    if (song == NULL)
        return;
    play_song(song->data);
    playlist->last_song = song;
}

void play_next(playlist_t *playlist, music_queue_t *q) // TODO: play the next song in the linked list if the queue is empty. If the queue if not empty, play from the queue
{
    if (empty(q))
    {
        if (playlist->last_song == NULL)
        {
            song_t *cur;
            cur = playlist->list->head;
            play_song(cur->data);
            playlist->last_song = cur;
        }
        else
        {
            song_t *temp = playlist->last_song;
            if (temp->next == NULL)
            {
                song_t *cur1 = NULL;
                cur1 = (song_t *)malloc(sizeof(song_t));
                cur1 = playlist->list->head;
                play_song(cur1->data);
                playlist->last_song = cur1;
            }
            else
            {
                play_song(temp->next->data);
                playlist->last_song = temp->next;
            }
        }
    }
    else
    {
        play_from_queue(q);
    }
}

void play_previous(playlist_t *playlist) // TODO: play the previous song from the linked list
{
    if (is_empty(playlist->list))
        return;

    if (playlist->last_song == NULL)
    {
        song_t *cur1;
        cur1 = playlist->list->tail;
        play_song(cur1->data);
        playlist->last_song = cur1;
    }
    else
    {
        song_t *cur;
        cur = playlist->last_song;
        if (cur->prev == NULL)
        {
            song_t *cur2;
            cur2 = playlist->list->tail;
            play_song(cur2->data);
            playlist->last_song = cur2;
        }
        else
        {
            play_song(cur->prev->data);
            playlist->last_song = cur->prev;
        }
    }
}

void play_from_queue(music_queue_t *q) // TODO: play a song from the queue
{
    song_t *cur = q->front;
    play_song(cur->data);
}

void insert_to_queue(music_queue_t *q, int song_id) // TODO: insert a song id to the queue
{
    enqueue(q, song_id);
}

void reverse(playlist_t *playlist) // TODO: reverse the order of the songs in the given playlist. (Swap the nodes, not data)
{
    song_t *cur = playlist->list->head;
    song_t *temp = NULL;
    while (cur)
    {
        temp = cur->prev;
        cur->prev = cur->next;
        cur->next = temp;
        cur = cur->prev;
    }
    playlist->list->tail = playlist->list->head;
    if (temp != NULL)
    {
        playlist->list->head = temp->prev;
    }
}

void k_swap(playlist_t *playlist, int k) // TODO: swap the node at position i with node at position i+k upto the point where i+k is less than the size of the linked list
{
    int size = playlist->list->size;
    song_t *node2, *node1, *prev1, *prev2, *next1, *next2, *cur1;
    cur1 = playlist->list->head;

    for (int i = 0; i + k < size; i++)
    {
        node1 = cur1;
        node2 = cur1;
        for (int j = 0; j < k; j++)
        {
            prev2 = node2;
            node2 = node2->next;
        }
        if (node1->next == node2)
        {
            if (node2->next == NULL)
                node1->next = NULL;
            else
            {
                node1->next = node2->next;
                node1->next->prev = node1;
            }
            node2->next = node1;
            if (node1->prev == NULL)
            {
                node2->prev = NULL;
                playlist->list->head = node2;
            }
            else
            {
                node2->prev = node1->prev;
                prev1 = node1->prev;
                prev1->next = node2;
            }
            node1->prev = node2;
        }

        else if (node2)
        {
            prev1 = node1->prev;
            prev2 = node2->prev;
            next1 = node1->next;
            next2 = node2->next;

            if (next2)
            {
                node1->next = next2;
                next2->prev = node1;
            }
            else
            {
                node1->next = NULL;
            }

            node1->prev = prev2;
            node2->next = next1;

            if (next1 == prev2)
            {
                prev2->prev = node2;
            }
            else
            {
                next1->prev = node2;
            }
            prev2->next = node1;

            if (prev1)
            {
                node2->prev = prev1;
                prev1->next = node2;
            }
            else
            {
                node2->prev = NULL;
                playlist->list->head = node2;
            }
        }
        cur1 = node2->next;
    }
}

void shuffle(playlist_t *playlist, int k) // TODO: perform k_swap and reverse
{
    k_swap(playlist, k);
    reverse(playlist);
}

song_t *debug(playlist_t *playlist) // TODO: if the given linked list has a cycle, return the start of the cycle, else return null. Check cycles only in forward direction i.e with the next pointer. No need to check for cycles in the backward pointer.
{
    song_t *node2 = playlist->list->tail;
    if (node2->next != NULL)
        return node2->next;
}

void display_playlist(playlist_t *p) // Displays the playlist
{
    // DO NOT MODIFY!!!
    display_list(p->list);
}

void play_song(int song_id)
{
    // DO NOT MODIFY!!!
    printf("Playing: %d\n", song_id);
}