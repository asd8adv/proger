cmake_minimum_required(VERSION 3.2)
project(proger)
set(CMAKE_CXX_STANDARD 20)
set(SOURCES_PATH ${CMAKE_SOURCE_DIR}/source)
set(HEADERS
	${SOURCES_PATH}/notificator.h
	${SOURCES_PATH}/button.h
	${SOURCES_PATH}/buttonManager.h
	${SOURCES_PATH}/magicBox.h
	${SOURCES_PATH}/drawable.h
	${SOURCES_PATH}/goal.h
	${SOURCES_PATH}/wallClock.h
	${SOURCES_PATH}/player.h
	${SOURCES_PATH}/calendar.h
	${SOURCES_PATH}/messages.h
	${SOURCES_PATH}/dictionary.h	
	${SOURCES_PATH}/windowManager.h
	${SOURCES_PATH}/drawableObjects.h
)
set (SOURCES
	${SOURCES_PATH}/main.cpp
	${SOURCES_PATH}/notificator.cpp
	${SOURCES_PATH}/button.cpp
	${SOURCES_PATH}/buttonManager.cpp
	${SOURCES_PATH}/drawable.cpp
	${SOURCES_PATH}/goal.cpp
	${SOURCES_PATH}/wallClock.cpp
	${SOURCES_PATH}/player.cpp
	${SOURCES_PATH}/calendar.cpp
	${SOURCES_PATH}/messages.cpp
	${SOURCES_PATH}/dictionary.cpp	
	${SOURCES_PATH}/windowManager.cpp
	${SOURCES_PATH}/drawableObjects.cpp		
)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)