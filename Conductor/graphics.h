#pragma once

#include "track.h"
#include "level.h"
#include "raylib.h"
#include "raymath.h"

constexpr float ANIMATION_TICK_INTERVAL = 0.05f;

class Graphics {
public:
	static void init(const char* backgroundTexture, std::vector<std::string> conductorSprites);
	static void drawRenderTexture(Track& track);
	static void renderTrack();
	static RenderTexture2D& getTrackRenderTexture();
	static void drawBackground();
	static void drawConductor(Level& level);
	static bool updateAnimationTick();
	static void drawHitLine(Level& level);
private:
	static Model m_track_plane;
	static RenderTexture2D m_track_plane_tex;
	static Texture2D m_background_tex;

	static std::vector<Texture2D> m_conductor_sprites;
	static int m_conductor_anim_phase;
	static int m_conductor_anim_target;
	static bool m_conductor_baton_prev;

	static float m_tick_time;
	static float m_shake_multiplier;
};