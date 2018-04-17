/**
 * @file SonarLandingCtrl.hpp
 * Class to control the drone for landing on a platform using a sonar.
 * Designed for the LIS-EPFL DroneCourse
 *
 * @author Arthur Gay <arthur.gay@epfl.ch>
 */

// TODO: clean the code

#pragma once
#include <px4_posix.h>
#include "PositionCtrl.hpp"
#include "BaseCtrl.hpp"

class SonarLandingCtrl : public PositionCtrl
{


public:

	/**
	 * Constructor
	 *
	 * @param gimbal     Gimbal controller to control pitch and yaw of gimbal
	 */
	SonarLandingCtrl(GimbalCtrl &gimbal);

	~SonarLandingCtrl() {};

	/**
	 * Check if goal is reached
	 * i.e. if we are close enough to waypoint
	 * (acceptance radius define with parameter POS_ACCEPT_RAD)
	 *
	 * @return  True if distance to goal smaller than POS_ACCEPT_RAD
	 */
	virtual bool is_goal_reached();

	/**
	 * Updates the controller
	 * i.e. calculates velocity to reach goal position
	 * and sends it using BaseCtrl::send_velocity_command(...)
	 *
	 * @return  drone position in local frame
	 */
	void update();

protected:

	/**
	 * Updates uORB subscriptions:
	 * i.e. updates _current_pos with vehicle_local_position uORB message
	 */
	void update_subscriptions();


	/**
	 * Updates onboard parameters:
	 * i.e. update POS_ACCEPT_RAD
	 */
	void update_parameters();

private:
	int search_counter;
	
	int _local_pos_sub;
	/** Subscriber handle for the distance_sensor uORB topic */
	int _distance_sensor_sub;

	int _ground_contact_sub;
	/** Current distance measured by the sonar */
	float _current_distance;
	/** Set this flag to true if the drone is over the platform */
	bool _platform_detected;
	/** Set this flag to true if the platform has been found */
	bool _platform_found;

	bool _landed;
	bool _ground_detected;

	matrix::Vector3f _current_pos;
	matrix::Vector3f pos;
	
	float _current_pos_save_1;
	float _current_pos_save_2;
	float _current_pos_save_3;
	float _current_pos_save_4;

	float pos_landing_x;
	float pos_landing_y;

	param_t _p_accept_rad;
	float	_pos_accept_rad;

	/**
	 * Execute the search algorithm.
	 * @return true if the drone is ready to land
	 */
	bool update_search();
	/**
	 * Execute the landing sequence.
	 * @return true if the drone has landed
	 */
	bool update_landing();

};
