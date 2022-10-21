#pragma once
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 640
#define INFO_PATH config/gameInfo.csv
#define PRINT(STR) std::cout<<STR<<std::endl
#define RESOURCES_CSV "resources.csv"
#define STAGE_PATH_NAME(EPISODE_NAEM) "config/" + (string)EPISODE_NAEM +"/resources.csv"
#define STAGE_PATH_NUM(EPISODE_NUM) "config/episode" + to_string(EPISODE_NUM) +"/resources.csv"