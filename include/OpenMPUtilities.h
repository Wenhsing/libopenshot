/**
 * @file
 * @brief Header file for OpenMPUtilities (set some common macros)
 * @author Jonathan Thomas <jonathan@openshot.org>
 *
 * @ref License
 */

/* LICENSE
 *
 * Copyright (c) 2008-2014 OpenShot Studios, LLC
 * <http://www.openshotstudios.com/>. This file is part of
 * OpenShot Library (libopenshot), an open-source project dedicated to
 * delivering high quality video editing and animation solutions to the
 * world. For more information visit <http://www.openshot.org/>.
 *
 * OpenShot Library (libopenshot) is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * OpenShot Library (libopenshot) is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with OpenShot Library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OPENSHOT_OPENMP_UTILITIES_H
#define OPENSHOT_OPENMP_UTILITIES_H

#include <omp.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Settings.h"

using namespace std;
using namespace openshot;

// Calculate the # of OpenMP Threads to allow
#define OPEN_MP_NUM_PROCESSORS (min(omp_get_num_procs(), max(2, openshot::Settings::Instance()->OMP_THREADS) ))
#define FF_NUM_PROCESSORS (min(omp_get_num_procs(), max(2, openshot::Settings::Instance()->FF_THREADS) ))


#endif
