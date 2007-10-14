//     ____                _       __               
//    / __ )____  _____   | |     / /___ ___________
//   / __  / __ \/ ___/   | | /| / / __ `/ ___/ ___/
//  / /_/ / /_/ (__  )    | |/ |/ / /_/ / /  (__  ) 
// /_____/\____/____/     |__/|__/\__,_/_/  /____/  
//                                              
//       A futuristic real-time strategy game.
//          This file is part of Bos Wars.
//
/**@name smokeparticle.cpp - The smoke particle. */
//
//      (c) Copyright 2007 by Jimmy Salmon
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; only version 2 of the License.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//      02111-1307, USA.
//
//      $Id: commands.cpp 9147 2007-09-28 17:18:24Z jim4 $

//@{

#include "stratagus.h"
#include "particle.h"
#include "video.h"


CGraphic *CSmokeParticle::lightSmoke;
CGraphic *CSmokeParticle::darkSmoke;
int CSmokeParticle::numFrames = 26;


CSmokeParticle::CSmokeParticle(CPosition position) :
	CParticle(position), frame(0), currTicks(0)
{
	if (MyRand() % 2 == 0) {
		g = lightSmoke;
	} else {
		g = darkSmoke;
	}
}

CSmokeParticle::~CSmokeParticle()
{
}

void CSmokeParticle::init()
{
	if (!lightSmoke) {
		lightSmoke = CGraphic::New("graphics/particle/smokelight48.png", 48, 48);
		lightSmoke->Load();
	}
	if (!darkSmoke) {
		darkSmoke = CGraphic::New("graphics/particle/smokedark48.png", 48, 48);
		darkSmoke->Load();
	}
}

void CSmokeParticle::exit()
{
	if (lightSmoke) {
		CGraphic::Free(lightSmoke);
		lightSmoke = NULL;
	}
	if (darkSmoke) {
		CGraphic::Free(darkSmoke);
		darkSmoke = NULL;
	}
}

void CSmokeParticle::draw()
{
	g->DrawFrameClip(frame, pos.x - g->Width / 2, pos.y - g->Height / 2);
}

void CSmokeParticle::update(int ticks)
{
	const int ticksPerFrame = 45;
	currTicks += ticks;
	while (currTicks > ticksPerFrame) {
		currTicks -= ticksPerFrame;
		++frame;
	}
	if (frame >= numFrames) {
		destroy();
	}

	// smoke rises
	const int smokeRisePerSecond = 32;
	pos.y -= ticks / 1000.f * smokeRisePerSecond;
}

//@}
