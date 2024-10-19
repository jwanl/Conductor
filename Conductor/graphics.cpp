#include "graphics.h"
#include <cmath>
#include <iostream>
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
	ClearBackground(ColorAlpha(WHITE, 0.4f));
	
	auto sub = track.getNextValues();
	double leftSide = track.getTime();

	for (int i = 0; i < 4; i++) {
		const auto y = i * 64 / 4;
		DrawLine(0, y, 511, y, ColorAlpha(BLACK, 0.8f));
	}
	DrawLine(0, 63, 511, 63, ColorAlpha(BLACK, 0.8f));

	for (const auto& item : sub)
	{
		
		const auto& tex = track.m_objects[item.i];
		//DrawTextureEx(tex, { (item.x - (float)leftSide) * 128.0f, item.y * 64.0f + 32.0f }, 180.0f, 1.0f, WHITE);
		DrawTextureRec(tex, Rectangle{ 0, 0  , (float)tex.width, -(float)tex.height }, { (item.x - (float)leftSide) * 128.0f, item.y * 64.0f + 32.0f }, GREEN);
		//DrawTexture(tex, (item.x - leftSide) * 128, item.y * 64 + 32, WHITE);
		//DrawCircle((item.x - leftSide) * 128, item.y * 64 + 32, 8, BLUE);


	}

	
	
}


void Graphics::renderTrack()
{
	// demo code to find a good orientation for track plane
	//if (IsKeyDown(KEY_M)) angle += 1.0f;
	//if (IsKeyDown(KEY_N)) angle -= 1.0f;
	//if (IsKeyDown(KEY_LEFT)) rax.x += 0.005f;
	//if (IsKeyDown(KEY_RIGHT)) rax.x -= 0.005f;
	//if (IsKeyDown(KEY_UP)) rax.y += .005f;
	//if (IsKeyDown(KEY_DOWN)) rax.y -= .005f;
	//if (IsKeyDown(KEY_O)) rax.z += .005f;
	//if (IsKeyDown(KEY_L)) rax.z -= .005f;

	Vector3 pos = { 0.8f, -2.25f, 0.1f };
	Vector3 rax = { 0.93099f, -0.365046f, 0.0f };
	float angle = 180.0f;
	//rax = Vector3Normalize(rax);
	//std::cout << rax.x << " : " << rax.y << " : " << rax.z << "\n";

	Vector3 size = { 1.0f, 1.0f, 1.0f };

	DrawModelEx(m_track_plane, pos, rax, angle, size, WHITE);
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