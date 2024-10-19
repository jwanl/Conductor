#include "graphics.h"
#include <cmath>
Model Graphics::m_track_plane;
RenderTexture2D Graphics::m_track_plane_tex;
Texture2D Graphics::m_background_tex;
std::vector<Texture2D> Graphics::m_conductor_sprites;
int Graphics::m_conductor_anim_phase;
int Graphics::m_conductor_anim_target;
bool Graphics::m_conductor_baton_prev;
float Graphics::m_tick_time;

void Graphics::init(const char* backgroundTexture, std::vector<std::string> conductorSprites)
{
	Mesh planeMesh = GenMeshPlane(8.0f, 0.5f, 1, 1);
	m_track_plane = LoadModelFromMesh(planeMesh);
	m_track_plane_tex = LoadRenderTexture(512, 64);
	SetMaterialTexture(m_track_plane.materials, 0, m_track_plane_tex.texture);

	m_background_tex = LoadTexture(backgroundTexture);

	// load conductor sprite sheet
	for (auto& sprite : conductorSprites)
	{
		m_conductor_sprites.push_back(LoadTexture(sprite.c_str()));
	}

	m_conductor_anim_phase = 0;
	m_conductor_anim_target = 0;
	m_conductor_baton_prev = false;
	m_tick_time = 0.0f;
}

RenderTexture2D& Graphics::getTrackRenderTexture()
{
	return m_track_plane_tex;
}

/* Draws to track render texture. Remember to change drawing mode first and after */
void Graphics::drawRenderTexture(Track& track)
{
	ClearBackground(ColorAlpha(WHITE, 0.0f));
	
	auto sub = track.getNextValues();
	double leftSide = track.getTime();
	for (Vector2& item : sub)
	{
		DrawCircle((item.x - leftSide) * 128, item.y * 64 + 32, 8, BLUE);
	}
}

void Graphics::renderTrack()
{
	Vector3 pos = { 1.8f, 0.3f, 0.3f };
	Vector3 rax = { 0.970f, 0.0f, 0.0242f };
	Vector3 size = { 1.0f, 1.0f, 1.0f };

	DrawModelEx(m_track_plane, pos, rax, 185.539f, size, WHITE);
}




void Graphics::drawBackground()
{
	
	/*const auto t = GetTime();
	const auto dx = std::sin(t * 200) + std::cos(t * 17);
	const auto dy = std::cos(t * 20) + std::sin(t * 150);
	DrawTexture(m_background_tex, 10 * dx, 10 * dy, WHITE);*/
	DrawTexture(m_background_tex, 0, 0, WHITE);
}

void Graphics::drawConductor(Level& level)
{
	if (level.isBatonUp() && !m_conductor_baton_prev)
	{
		m_conductor_anim_target = 2;
		m_conductor_baton_prev = true;
	}
	else if (!level.isBatonUp() && m_conductor_baton_prev)
	{
		m_conductor_anim_target = 0;
		m_conductor_baton_prev = false;
	}

	// update animation phase
	if (updateAnimationTick())
	{
		if (m_conductor_anim_phase < m_conductor_anim_target)
			m_conductor_anim_phase++;
		else if (m_conductor_anim_phase > m_conductor_anim_target)
			m_conductor_anim_phase--;
	}

	float scale = 1.5f;

	DrawTextureEx(m_conductor_sprites.at(m_conductor_anim_phase), 
		{ (float)GetRenderWidth() / 2.0f - (128.0f * scale), (float)GetRenderHeight() - 350.0f },
		0.0f, scale, WHITE);
}

bool Graphics::updateAnimationTick()
{
	m_tick_time += GetFrameTime();
	if (m_tick_time > ANIMATION_TICK_INTERVAL)
	{
		m_tick_time -= ANIMATION_TICK_INTERVAL;
		return true;
	}
	return false;
}