/* ***********************************************************************
 * Tank Game Multiplayer
 * (C) 2018 by Yiannis Bourkelis (hello@andama.org)
 *
 * This file is part of Tank Game Multiplayer.
 *
 * Tank Game Multiplayer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank Game Multiplayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tank Game Multiplayer.  If not, see <http://www.gnu.org/licenses/>.
 * ***********************************************************************/

#include "viewport.h"

std::vector<Camera> ViewPort::allCameras;

//Screen dimensions
int ViewPort::ScreenWidth;
int ViewPort::ScreenHeight;

//Level dimensions
double ViewPort::levelWidth;
double ViewPort::levelHeight;

ViewPort::ViewPort()
{

}

ViewPort::~ViewPort()
{

}


void ViewPort::FollowEntity(TransformComponent &transformComponent, SpriteComponent &spriteComponent, ViewportTarget &viewportTarget, ViewPort& viewport, double levelWidth, double levelHeight)
{   
    //todo: remove these 2 variables
    auto cameraID = viewport.cameraID;
    auto entityScale = viewport.entityScale;

    levelWidth *= entityScale.x;
    levelHeight *= entityScale.y;

    //calculations do not need rounding because it causes the entity on camera to shake
    allCameras[cameraID].frame.x = static_cast<int>((transformComponent.Position.x * entityScale.x + (static_cast<double>(spriteComponent.sourceRectangle.w * entityScale.x) / 2.0) ) - (static_cast<double>(allCameras[cameraID].frame.w) / 2.0));
    allCameras[cameraID].frame.y = static_cast<int>((transformComponent.Position.y * entityScale.y + (static_cast<double>(spriteComponent.sourceRectangle.h * entityScale.y) / 2.0) ) - (static_cast<double>(allCameras[cameraID].frame.h) / 2.0));


    //Keep the camera in bounds
    if( allCameras[cameraID].frame.x < 0 )
    {
        allCameras[cameraID].frame.x = 0;
    }
    if( allCameras[cameraID].frame.y < 0 )
    {
        allCameras[cameraID].frame.y = 0;
    }
    if( allCameras[cameraID].frame.x  > (levelWidth - allCameras[cameraID].frame.w))
    {
        allCameras[cameraID].frame.x = static_cast<int>(levelWidth - allCameras[cameraID].frame.w);
    }
    if( allCameras[cameraID].frame.y  > (levelHeight - allCameras[cameraID].frame.h))
    {
        allCameras[cameraID].frame.y = static_cast<int>(levelHeight - allCameras[cameraID].frame.h);
    }
}

