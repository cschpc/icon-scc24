/**
 * @file grid_cell.c
 *
 * @copyright Copyright  (C)  2013 Moritz Hanke <hanke@dkrz.de>
 *                                 Rene Redler <rene.redler@mpimet.mpg.de>
 *                                 Thomas Jahns <jahns@dkrz.de>
 *
 * @version 1.0
 * @author Moritz Hanke <hanke@dkrz.de>
 *         Rene Redler <rene.redler@mpimet.mpg.de>
 *         Thomas Jahns <jahns@dkrz.de>
 */
/*
 * Keywords:
 * Maintainer: Moritz Hanke <hanke@dkrz.de>
 *             Rene Redler <rene.redler@mpimet.mpg.de>
 *             Thomas Jahns <jahns@dkrz.de>
 * URL: https://dkrz-sw.gitlab-pages.dkrz.de/yac/
 *
 * This file is part of YAC.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are  permitted provided that the following conditions are
 * met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the DKRZ GmbH nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "grid_cell.h"
#include "utils.h"
#include "ensure_array_size.h"
#include "geometry.h"

void yac_init_grid_cell(struct grid_cell * cell) {

   cell->coordinates_xyz = NULL;
   cell->edge_type = NULL;
   cell->num_corners = 0;
   cell->array_size = 0;
}

static void ensure_grid_cell_size(
  struct grid_cell * cell, size_t num_corners) {

  if (num_corners > cell->array_size) {
    cell->coordinates_xyz = xrealloc(cell->coordinates_xyz, num_corners *
                                     sizeof(*(cell->coordinates_xyz)));
    cell->edge_type = xrealloc(cell->edge_type, num_corners *
                               sizeof(*(cell->edge_type)));
    cell->array_size = num_corners;
  }
}

void yac_copy_grid_cell(struct grid_cell in_cell, struct grid_cell * out_cell) {

   ensure_grid_cell_size(out_cell, in_cell.num_corners);
   memcpy(out_cell->coordinates_xyz, in_cell.coordinates_xyz,
          in_cell.num_corners * sizeof(*(out_cell->coordinates_xyz)));
   memcpy(out_cell->edge_type, in_cell.edge_type,
          in_cell.num_corners * sizeof(*(out_cell->edge_type)));
   out_cell->num_corners = in_cell.num_corners;
}

void yac_free_grid_cell(struct grid_cell * cell) {

   if (cell->coordinates_xyz != NULL) free(cell->coordinates_xyz);
   if (cell->edge_type != NULL) free(cell->edge_type);

   yac_init_grid_cell(cell);
}

static void set_triangle(
  struct grid_cell cell, struct grid_cell * triangle, size_t idx[3]) {

  ensure_grid_cell_size(triangle, 3);
  for (size_t i = 0; i < 3; ++i) {
    size_t curr_idx = idx[i];
    triangle->coordinates_xyz[i][0] = cell.coordinates_xyz[curr_idx][0];
    triangle->coordinates_xyz[i][1] = cell.coordinates_xyz[curr_idx][1];
    triangle->coordinates_xyz[i][2] = cell.coordinates_xyz[curr_idx][2];
    triangle->edge_type[i] = GREAT_CIRCLE_EDGE;
  }
  triangle->num_corners = 3;
}

void yac_triangulate_cell(
  struct grid_cell cell, size_t start_corner, struct grid_cell * triangles) {

  size_t num_corners = cell.num_corners;

  YAC_ASSERT(num_corners >= 3, "ERROR(yac_triangulate_cell): number < 3")

  switch (num_corners) {
    case(3):
      if (start_corner == 0) {
        yac_copy_grid_cell(cell, triangles);
        return;
      }

      set_triangle(
        cell, triangles,
        (size_t [3]){(size_t)((start_corner + 0)%3),
                     (size_t)((start_corner + 1)%3),
                     (size_t)((start_corner + 2)%3)});
      return;
    case(4): {
      size_t idx[5] = {(size_t)((start_corner + 0)%num_corners),
                       (size_t)((start_corner + 1)%num_corners),
                       (size_t)((start_corner + 2)%num_corners),
                       (size_t)((start_corner + 3)%num_corners),
                       (size_t)((start_corner + 0)%num_corners)};
      set_triangle(cell, triangles + 0, &(idx[0]));
      set_triangle(cell, triangles + 1, &(idx[2]));
      return;
    }
    case(5): {
      size_t idx[7] = {(size_t)((start_corner + 0)%num_corners),
                       (size_t)((start_corner + 1)%num_corners),
                       (size_t)((start_corner + 2)%num_corners),
                       (size_t)((start_corner + 3)%num_corners),
                       (size_t)((start_corner + 4)%num_corners),
                       (size_t)((start_corner + 0)%num_corners),
                       (size_t)((start_corner + 2)%num_corners)};
      set_triangle(cell, triangles + 0, &(idx[0]));
      set_triangle(cell, triangles + 1, &(idx[2]));
      set_triangle(cell, triangles + 2, &(idx[4]));
      return;
    }
    case(6): {
      size_t idx[9] = {(size_t)((start_corner + 0)%num_corners),
                       (size_t)((start_corner + 1)%num_corners),
                       (size_t)((start_corner + 2)%num_corners),
                       (size_t)((start_corner + 3)%num_corners),
                       (size_t)((start_corner + 4)%num_corners),
                       (size_t)((start_corner + 5)%num_corners),
                       (size_t)((start_corner + 0)%num_corners),
                       (size_t)((start_corner + 2)%num_corners),
                       (size_t)((start_corner + 4)%num_corners)};
      set_triangle(cell, triangles + 0, &(idx[0]));
      set_triangle(cell, triangles + 1, &(idx[2]));
      set_triangle(cell, triangles + 2, &(idx[4]));
      set_triangle(cell, triangles + 3, &(idx[6]));
      return;
    }
    default: {

      size_t temp_corner_indices[2*num_corners];
      size_t j = 0;
      for (size_t i = start_corner; i < num_corners; ++i, ++j)
        temp_corner_indices[j] = i;
      for (size_t i = 0; i < start_corner; ++i, ++j)
        temp_corner_indices[j] = i;

      for (size_t i = 0; i < num_corners - 2; ++i, ++j) {
        set_triangle(
          cell, triangles + i, &(temp_corner_indices[2 * i]));
        temp_corner_indices[j] = temp_corner_indices[2 * i];
      }
      return;
    }
  }
}

void yac_triangulate_cell_indices(
  size_t const * corner_indices, size_t num_corners, size_t start_corner,
  size_t (*triangle_indices)[3]) {

  YAC_ASSERT(
    num_corners >= 3, "ERROR(yac_triangulate_corner_indices): number < 3")

  switch (num_corners) {
    case(3):
      triangle_indices[0][0] = corner_indices[(start_corner + 0)%3];
      triangle_indices[0][1] = corner_indices[(start_corner + 1)%3];
      triangle_indices[0][2] = corner_indices[(start_corner + 2)%3];
      return;
    case(4):
      triangle_indices[0][0] = corner_indices[start_corner];
      triangle_indices[0][1] = corner_indices[(start_corner + 1)%4];
      triangle_indices[0][2] = corner_indices[(start_corner + 2)%4];
      triangle_indices[1][0] = corner_indices[(start_corner + 2)%4];
      triangle_indices[1][1] = corner_indices[(start_corner + 3)%4];
      triangle_indices[1][2] = corner_indices[start_corner];
      return;
    case(6):
      triangle_indices[0][0] = corner_indices[start_corner];
      triangle_indices[0][1] = corner_indices[(start_corner + 1)%6];
      triangle_indices[0][2] = corner_indices[(start_corner + 2)%6];
      triangle_indices[1][0] = corner_indices[(start_corner + 2)%6];
      triangle_indices[1][1] = corner_indices[(start_corner + 3)%6];
      triangle_indices[1][2] = corner_indices[(start_corner + 4)%6];
      triangle_indices[2][0] = corner_indices[(start_corner + 4)%6];
      triangle_indices[2][1] = corner_indices[(start_corner + 5)%6];
      triangle_indices[2][2] = corner_indices[start_corner];
      triangle_indices[3][0] = corner_indices[start_corner];
      triangle_indices[3][1] = corner_indices[(start_corner + 2)%6];
      triangle_indices[3][2] = corner_indices[(start_corner + 4)%6];
      return;
    default: {
      size_t temp_corner_indices[2*num_corners];
      size_t j = 0;
      for (size_t i = start_corner; i < num_corners; ++i, ++j)
        temp_corner_indices[j] = corner_indices[i];
      for (size_t i = 0; i < start_corner; ++i, ++j)
        temp_corner_indices[j] = corner_indices[i];

      for (size_t i = 0; i < num_corners - 2; ++i, ++j) {
        memcpy(triangle_indices[i], temp_corner_indices + 2 * i,
               3 * sizeof(*temp_corner_indices));
        temp_corner_indices[j] = temp_corner_indices[2 * i];
      }
      return;
    }
  }
}

#ifdef YAC_DEBUG_GRID_CELL
void print_grid_cell(FILE * stream, struct grid_cell cell, char * name) {

  char * out = NULL;
  size_t out_array_size = 0;
  size_t out_size = 0;

  if (name != NULL) {

      out_size = strlen(name) + 1 + 1 + 1;
      ENSURE_ARRAY_SIZE(out, out_array_size, out_size);

      strcpy(out, name);
      strcat(out, ":\n");
  }

  for (size_t i = 0; i < cell.num_corners; ++i) {

      char buffer[1024];

      double coordinates_x, coordinates_y;
      XYZtoLL(cell.coordinates_xyz[i], &coordinates_x, &coordinates_y);
      sprintf(buffer, "%d x %.16f y %.16f %s\n", i,
              coordinates_x, coordinates_y,
             (cell.edge_type[i] == LAT_CIRCLE_EDGE)?("LAT_CIRCLE_EDGE"):
            ((cell.edge_type[i] == LON_CIRCLE_EDGE)?("LON_CIRCLE_EDGE"):
             ("GREAT_CIRCLE_EDGE")));

      out_size += strlen(buffer);

      ENSURE_ARRAY_SIZE(out, out_array_size, out_size);

      strcat(out, buffer);
  }

  if (out != NULL)
    fputs(out, stream);

  free(out);
}
#endif
