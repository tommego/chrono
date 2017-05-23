// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2016 projectchrono.org
// All right reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Nic Olsen
// =============================================================================

#pragma once

#include "chrono_distributed/ChApiDistributed.h"
#include "chrono_distributed/physics/ChSystemDistributed.h"
#include "chrono_distributed/other_types.h"

#include "chrono_parallel/math/other_types.h"
#include "chrono_parallel/ChDataManager.h"

#include <vector>

namespace chrono {

class ChSystemDistributed;

class CH_DISTR_API ChDistributedDataManager {
public:
	ChDistributedDataManager(ChSystemDistributed *my_sys);
	virtual ~ChDistributedDataManager();

	std::vector<unsigned int> global_id; ///< Global id of each body
	std::vector<distributed::COMM_STATUS> comm_status; ///< Communication status of each body

	ChParallelDataManager *data_manager;
	ChSystemDistributed *my_sys;

	std::vector<int> body_shape_start; ///< Start index in body_shapes of the shapes associated with this BODY
	std::vector<int> body_shape_count; ///< Number of shapes associated with this BODY
	std::vector<int> body_shapes; ///< Indices of shape in DATA_MANAGER->shape_data for a given SHAPE

	// TODO: Need to track open spots in: data_manager->shape_data, this->body_shapes
	// DON'T need to track open spots in this->body_shape_start/count because those correspond with a BODY index
	// and therefore can be checked for validity by checking the body status

	// When receiving a body and adding its collision shapes, need 1)to find a spot in body shapes large enough for all of the
	// body's shapes, 2) Find individual slots in data_manager->shape_data to index to from body_shapes

	std::vector<bool> my_free_shapes;	///< Indicates that the free spaces in body_shapes
	std::vector<bool> dm_free_shapes;	///< Indicates that the space in the data_manager->shape_data is available



	//std::vector<int> ghosts; // TODO
/*
	int num_sharedup;
	int num_shareddown;
	int num_ghostup;
	int num_ghostdown;
*/

	/// Returns the local index of a body, given its global id
	int GetLocalIndex(unsigned int gid);
};
} /* namespace chrono */