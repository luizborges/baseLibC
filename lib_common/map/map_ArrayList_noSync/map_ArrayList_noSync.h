/**
 */
#ifndef MAP_ARRAYLIST_NOSYNC_H
#define MAP_ARRAYLIST_NOSYNC_H

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <headers/memoryManager.h>
#include <headers/error.h>
#include <headers/arrayList_noSync.h>

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////
typedef struct {
  char *key;
  void *content;
} Map_ArrayList_noSync_cell_o;

typedef struct {
  ArrayList_noSync_t list;
} Map_ArrayList_noSync_o;

////////////////////////////////////////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////////////////////////////////////////
typedef Map_ArrayList_noSync_cell_o* Map_ArrayList_noSync_cell_t;
typedef Map_ArrayList_noSync_o* Map_ArrayList_noSync_t;

////////////////////////////////////////////////////////////////////////////////
// Constructs
////////////////////////////////////////////////////////////////////////////////
extern Map_ArrayList_noSync_t Map_ArrayList_noSync_New();


////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

extern void *Map_ArrayList_noSyncget (const void *_map, const char *key);
extern void *Map_ArrayList_noSyncset (void *_map, const char *key, const void *content);
extern void *Map_ArrayList_noSyncdel (void *_map, const char *key);
extern int   Map_ArrayList_noSynckeys(const void *_map, char **keys);
extern void  Map_ArrayList_noSyncend (void *_map);

#ifdef __cplusplus
}
#endif
#endif // MAP_ARRAYLIST_NOSYNC_H

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////




