cmake_minimum_required(VERSION 2.8)

# set(CMAKE_VERBOSE_MAKEFILE ON CACHE STRING "" FORCE)

set(CMAKE_C_COMPILER_WORKS 1 CACHE STRING "" FORCE)

SET(CMAKE_C_COMPILER i686-w64-mingw32-gcc CACHE STRING "" FORCE)
SET(CMAKE_C_LINK_EXECUTABLE i686-w64-mingw32-gcc CACHE STRING "" FORCE)

project(quake2)

SET(QUAKE_2_SRC
		src/m_rider.h
		src/m_player.h
		src/game.h
		src/g_local.h

		src/g_ai.c
		src/p_client.c
		src/g_cmds.c
		src/g_svcmds.c
		src/g_chase.c
		src/g_combat.c
		src/g_func.c
		src/g_items.c
		src/g_main.c
		src/g_misc.c
		src/g_monster.c
		src/g_phys.c
		src/g_save.c
		src/g_spawn.c
		src/g_target.c
		src/g_trigger.c
		src/g_turret.c
		src/g_utils.c
		src/g_weapon.c
		src/m_actor.c
		src/m_berserk.c
		src/m_boss2.c
		src/m_boss3.c
		src/m_boss31.c
		src/m_boss32.c
		src/m_brain.c
		src/m_chick.c
		src/m_flipper.c
		src/m_float.c
		src/m_flyer.c
		src/m_gladiator.c
		src/m_gunner.c
		src/m_hover.c
		src/m_infantry.c
		src/m_insane.c
		src/m_medic.c
		src/m_move.c
		src/m_mutant.c
		src/m_parasite.c
		src/m_soldier.c
		src/m_supertank.c
		src/m_tank.c
		src/p_hud.c
		src/p_trail.c
		src/p_view.c
		src/p_weapon.c
		src/q_shared.c
		src/m_flash.c

		src/mod/q2includewrapper.h

		src/mod/weapon.c
		src/mod/sh_bullet.c
		src/mod/mod.c)

add_library(quake2 SHARED ${QUAKE_2_SRC})

set_target_properties(quake2 PROPERTIES
		PREFIX "${CMAKE_SOURCE_DIR}/engine/baseq2/"
		OUTPUT_NAME "gamex86"
		SUFFIX ".dll"
		LINK_FLAGS "-fPIC -shared"
		DEFINE_SYMBOL ""
		CACHE STRING "" FORCE)

include_directories(src)
target_compile_options(quake2 PUBLIC -fPIC -Dstricmp=strcasecmp -g)