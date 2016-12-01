#ifndef __STABILIZER_TYPES_H__
#define __STABILIZER_TYPES_H__
#pragma anon_unions
#include <stdint.h>
#include <stdbool.h>
//#include "../../Devices/imu_types.h"

/* Orientation as a quaternion */
typedef struct quaternion_s {
  uint32_t timestamp;
  union {
    struct {
      float q0;
      float q1;
      float q2;
      float q3;
    };
    struct {
      float x;
      float y;
      float z;
      float w;
    };
  };
} quaternion_t;

typedef struct rotation_s {
  uint32_t timestamp;  // Timestamp when the data was computed
	float R[3][3];
} rotation_t;

/* x,y,z vector */
struct vec3f_s {
  uint32_t timestamp; // Timestamp when the data was computed
	union {
    struct {
      float R;
      float P;
      float Y;
    };
    struct {
      float x;
      float y;
      float z;
    };
		float v[3];
  };
};
typedef struct vec3f_s vec3f_t;
//typedef struct vec3f_s moment_t;
//typedef struct vec3f_s euler_t;
//typedef struct vec3f_s angularRate_t;
struct vec3i16_s {
	uint32_t timestamp;
	union {
   struct {
         int16_t x;
         int16_t y;
         int16_t z;
   };
   int16_t v[3];
 };
};
//typedef struct vec3i16_s acc_raw_t;
//typedef struct vec3i16_s gyr_raw_t;
//typedef struct vec3i16_s mag_raw_t;
typedef struct vec3i16_s vec3i16_t;

typedef struct margData_s {
	vec3f_t acc;
	vec3f_t gyr;
	vec3f_t mag;
	bool mag_updated;
} marg_t;//used in queue

typedef struct battery_s {
  uint16_t voltage;
} battery_t;//used in queue

typedef struct state_s {
//  euler_t Euler;
	quaternion_t Q;
	rotation_t R;
	vec3f_t rate;
} state_t;//used in queue

typedef struct command_s {
	quaternion_t Q;
	float thrust;
} command_t;//used in queue

typedef struct setpoint_s {
	rotation_t R;
	float thrust;
} setpoint_t;//used in queue

typedef struct output_s {
	vec3f_t moment;
	float thrust;
} output_t;//used in queue

typedef enum mode_e {
  modeDisable = 0,
  modeAbs,
  modeVelocity
} mode_t;

// Frequencies to bo used with the RATE_DO_EXECUTE_HZ macro. Do NOT use an arbitrary number.
#define RATE_1000_HZ 1000
#define RATE_500_HZ 500
#define RATE_250_HZ 250
#define RATE_100_HZ 100
#define RATE_50_HZ 50
#define RATE_25_HZ 25

#ifdef ESTIMATOR_TYPE_kalman
#define RATE_MAIN_LOOP RATE_1000_HZ
#else
#define RATE_MAIN_LOOP RATE_1000_HZ
#endif

#define RATE_DO_EXECUTE(RATE_HZ, TICK) ((TICK % (RATE_MAIN_LOOP / RATE_HZ)) == 0)

#endif