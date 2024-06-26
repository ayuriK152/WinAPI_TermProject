#pragma once

static const int POSITION_REFRESH_ID			= 1000;
static const int ANIMATION_REFRESH_ID_PLAYER	= 1001;
static const int ANIMATION_REFRESH_ID_ENEMY		= 2001;
static const int AI_REFRESH_ID_ENEMY			= 3001;

static const int ANIMATION_REFRESH_DURATION				= 100;
static const int ANIMATION_REFRESH_DURATION_ENEMY		= 150;
static const int ANIMATION_REFRESH_DURATION_PLAYER_ROLL = 50;
static const int POSITION_REFRESH_DURATION				= 10;
static const int AI_REFRESH_REFRESH_DURATION			= 50;

static const int CREATURE_GUN_HOLDING_DISTANCE	= 40;
static const int ENEMY_STOP_DISTANCE			= 300;

static const int CURSOR_SIZE				= 33;
static const int PLAYER_CHARACTER_SIZE		= 75;
static const int ENEMY_BULLETJUNIOR_SIZE	= 75;
static const int PLAYER_HEART_SIZE			= 17;

static const int PLAYER_GUN_RELOAD_TIME		= 62;
static const int PLAYER_GUN_DELAY_TIME		= 30;
static const int ENEMY_GUN_DELAY_TIME		= 100;

static const int PLAYER_MOVE_SPEED					= 8;
static const int PLAYER_MOVE_SPEED_DIAGONAL			= 6;
static const int PLAYER_ROLL_START_SPEED			= 12;
static const int PLAYER_ROLL_ING_SPEED				= 5;
static const int PLAYER_ROLL_END_SPEED				= 6;
static const int PLAYER_ROLL_START_SPEED_DIAGONAL	= 8;
static const int PLAYER_ROLL_ING_SPEED_DIAGONAL		= 2;
static const int PLAYER_ROLL_END_SPEED_DIAGONAL		= 3;

static const int ENEMY_MOVE_SPEED_DEFAULT			= 3;
static const int ENEMY_MOVE_SPEED_DEFAULT_DIAGONAL	= 2;

static const POINT TILEMAP_OFFSET_INITPLACE_START	= { 0, 18 };
static const POINT TILEMAP_OFFSET_INITPLACE_END		= { 360, 342 };

#pragma region Animation Bitmap Offset
static const POINT ANIMATION_OFFSET_PLAYER_IDLE_UP		= { 150, 75 };
static const POINT ANIMATION_OFFSET_PLAYER_IDLE_DOWN	= { 150, 0 };
static const POINT ANIMATION_OFFSET_PLAYER_IDLE_LEFT	= { 150, 50 };
static const POINT ANIMATION_OFFSET_PLAYER_IDLE_RIGHT	= { 150, 50 };
static const POINT ANIMATION_OFFSET_PLAYER_IDLE_UPLEFT	= { 150, 100 };
static const POINT ANIMATION_OFFSET_PLAYER_IDLE_UPRIGHT = { 150, 100 };

static const POINT ANIMATION_OFFSET_PLAYER_MOVE_UP		= { 150, 175 };
static const POINT ANIMATION_OFFSET_PLAYER_MOVE_DOWN	= { 150, 125 };
static const POINT ANIMATION_OFFSET_PLAYER_MOVE_LEFT	= { 150, 150 };
static const POINT ANIMATION_OFFSET_PLAYER_MOVE_RIGHT	= { 150, 150 };
static const POINT ANIMATION_OFFSET_PLAYER_MOVE_UPLEFT	= { 150, 200 };
static const POINT ANIMATION_OFFSET_PLAYER_MOVE_UPRIGHT = { 150, 200 };

static const POINT ANIMATION_OFFSET_PLAYER_ROLL_UP		= { 0, 275 };
static const POINT ANIMATION_OFFSET_PLAYER_ROLL_DOWN	= { 0, 225 };
static const POINT ANIMATION_OFFSET_PLAYER_ROLL_LEFT	= { 0, 250 };
static const POINT ANIMATION_OFFSET_PLAYER_ROLL_RIGHT	= { 0, 250 };
static const POINT ANIMATION_OFFSET_PLAYER_ROLL_UPLEFT	= { 0, 300 };
static const POINT ANIMATION_OFFSET_PLAYER_ROLL_UPRIGHT = { 0, 300 };
#pragma endregion

static const int ENEMY_HP_BULLETJUNIOR	= 3;
static const int ENEMY_HP_SHOTGUNRED	= 5;
static const int ENEMY_HP_SHOTGUNBLUE	= 5;

static const double PI			= 3.14159265;
static const double TAN_22_5	= 0.41421356;
static const double TAN_67_5	= 2.41421356;