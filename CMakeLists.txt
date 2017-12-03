cmake_minimum_required(VERSION 2.8)

set(CMAKE_VERBOSE_MAKEFILE ON CACHE STRING "" FORCE)

set(CMAKE_C_COMPILER_WORKS 1 CACHE STRING "" FORCE)

SET(CMAKE_C_COMPILER i686-w64-mingw32-gcc CACHE STRING "" FORCE)
SET(CMAKE_C_LINK_EXECUTABLE i686-w64-mingw32-gcc CACHE STRING "" FORCE)

project(quake2)

SET(QUAKE_2_SRC
		g_ai.c
		p_client.c
		g_cmds.c
		g_svcmds.c
		g_chase.c
		g_combat.c
		g_func.c
		g_items.c
		g_main.c
		g_misc.c
		g_monster.c
		g_phys.c
		g_save.c
		g_spawn.c
		g_target.c
		g_trigger.c
		g_turret.c
		g_utils.c
		g_weapon.c
		m_actor.c
		m_berserk.c
		m_boss2.c
		m_boss3.c
		m_boss31.c
		m_boss32.c
		m_brain.c
		m_chick.c
		m_flipper.c
		m_float.c
		m_flyer.c
		m_gladiator.c
		m_gunner.c
		m_hover.c
		m_infantry.c
		m_insane.c
		m_medic.c
		m_move.c
		m_mutant.c
		m_parasite.c
		m_soldier.c
		m_supertank.c
		m_tank.c
		p_hud.c
		p_trail.c
		p_view.c
		p_weapon.c
		q_shared.c
		m_flash.c
		mod/weapon.c
		mod/sh_bullet.c
		mod/mod.c)

add_library(quake2 SHARED ${QUAKE_2_SRC})

set_target_properties(quake2 PROPERTIES
		PREFIX "${CMAKE_SOURCE_DIR}/engine/baseq2/"
		OUTPUT_NAME "gamex86"
		SUFFIX ".dll"
		LINK_FLAGS "-fPIC -shared"
		DEFINE_SYMBOL ""
		CACHE STRING "" FORCE)

target_compile_options(quake2 PUBLIC -fPIC -Dstricmp=strcasecmp -g)