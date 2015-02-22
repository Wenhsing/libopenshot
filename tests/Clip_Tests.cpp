/**
 * @file
 * @brief Unit tests for openshot::Clip
 * @author Jonathan Thomas <jonathan@openshot.org>
 *
 * @section LICENSE
 *
 * Copyright (c) 2008-2014 OpenShot Studios, LLC
 * <http://www.openshotstudios.com/>. This file is part of
 * OpenShot Library (libopenshot), an open-source project dedicated to
 * delivering high quality video editing and animation solutions to the
 * world. For more information visit <http://www.openshot.org/>.
 *
 * OpenShot Library (libopenshot) is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * OpenShot Library (libopenshot) is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with OpenShot Library. If not, see <http://www.gnu.org/licenses/>.
 */

#include "UnitTest++.h"
#include "../include/OpenShot.h"

using namespace std;
using namespace openshot;

TEST(Clip_Default_Constructor)
{
	// Create a empty clip
	Clip c1;

	// Check basic settings
	CHECK_EQUAL(ANCHOR_CANVAS, c1.anchor);
	CHECK_EQUAL(GRAVITY_CENTER, c1.gravity);
	CHECK_EQUAL(SCALE_FIT, c1.scale);
	CHECK_EQUAL(0, c1.Layer());
	CHECK_CLOSE(0.0f, c1.Position(), 0.00001);
	CHECK_CLOSE(0.0f, c1.Start(), 0.00001);
	CHECK_CLOSE(0.0f, c1.End(), 0.00001);
}

TEST(Clip_Constructor)
{
	// Create a empty clip
	Clip c1("../../src/examples/piano.wav");
	c1.Open();

	// Check basic settings
	CHECK_EQUAL(ANCHOR_CANVAS, c1.anchor);
	CHECK_EQUAL(GRAVITY_CENTER, c1.gravity);
	CHECK_EQUAL(SCALE_FIT, c1.scale);
	CHECK_EQUAL(0, c1.Layer());
	CHECK_CLOSE(0.0f, c1.Position(), 0.00001);
	CHECK_CLOSE(0.0f, c1.Start(), 0.00001);
	CHECK_CLOSE(4.39937f, c1.End(), 0.00001);
}

TEST(Clip_Basic_Gettings_and_Setters)
{
	// Create a empty clip
	Clip c1;

	// Check basic settings
	CHECK_THROW(c1.Open(), ReaderClosed);
	CHECK_EQUAL(ANCHOR_CANVAS, c1.anchor);
	CHECK_EQUAL(GRAVITY_CENTER, c1.gravity);
	CHECK_EQUAL(SCALE_FIT, c1.scale);
	CHECK_EQUAL(0, c1.Layer());
	CHECK_CLOSE(0.0f, c1.Position(), 0.00001);
	CHECK_CLOSE(0.0f, c1.Start(), 0.00001);
	CHECK_CLOSE(0.0f, c1.End(), 0.00001);

	// Change some properties
	c1.Layer(1);
	c1.Position(5.0);
	c1.Start(3.5);
	c1.End(10.5);

	CHECK_EQUAL(1, c1.Layer());
	CHECK_CLOSE(5.0f, c1.Position(), 0.00001);
	CHECK_CLOSE(3.5f, c1.Start(), 0.00001);
	CHECK_CLOSE(10.5f, c1.End(), 0.00001);
}

TEST(Clip_Properties)
{
	// Create a empty clip
	Clip c1;

	// Change some properties
	c1.Layer(1);
	c1.Position(5.0);
	c1.Start(3.5);
	c1.End(10.5);
	c1.alpha.AddPoint(1, 1.0);
	c1.alpha.AddPoint(500, 0.0);

	// Get properties JSON string at frame 1
	string properties = c1.PropertiesJSON(1);

	// Parse JSON string into JSON objects
	Json::Value root;
	Json::Reader reader;
	bool success = reader.parse( properties, root );
	if (!success)
		// Raise exception
		throw InvalidJSON("JSON could not be parsed (or is invalid)", "");

	try
	{
		// Check for specific things
		CHECK_CLOSE(1.0f, root["alpha"]["value"].asDouble(), 0.01);
		CHECK_EQUAL(true, root["alpha"]["keyframe"].asBool());
		CHECK_EQUAL(true, root["changed"]["value"].asBool());

	}
	catch (exception e)
	{
		// Error parsing JSON (or missing keys)
		throw InvalidJSON("JSON is invalid (missing keys or invalid data types)", "");
	}


	// Get properties JSON string at frame 250
	properties = c1.PropertiesJSON(250);

	// Parse JSON string into JSON objects
	root.clear();
	success = reader.parse( properties, root );
	if (!success)
		// Raise exception
		throw InvalidJSON("JSON could not be parsed (or is invalid)", "");

	try
	{
		// Check for specific things
		CHECK_CLOSE(0.5f, root["alpha"]["value"].asDouble(), 0.01);
		CHECK_EQUAL(false, root["alpha"]["keyframe"].asBool());
		CHECK_EQUAL(true, root["changed"]["value"].asBool());

	}
	catch (exception e)
	{
		// Error parsing JSON (or missing keys)
		throw InvalidJSON("JSON is invalid (missing keys or invalid data types)", "");
	}


	// Get properties JSON string at frame 250 (again)
	properties = c1.PropertiesJSON(250); // again

	// Parse JSON string into JSON objects
	root.clear();
	success = reader.parse( properties, root );
	if (!success)
		// Raise exception
		throw InvalidJSON("JSON could not be parsed (or is invalid)", "");

	try
	{
		// Check for specific things
		CHECK_EQUAL(false, root["alpha"]["keyframe"].asBool());
		CHECK_EQUAL(false, root["changed"]["value"].asBool());

	}
	catch (exception e)
	{
		// Error parsing JSON (or missing keys)
		throw InvalidJSON("JSON is invalid (missing keys or invalid data types)", "");
	}


	// Get properties JSON string at frame 500
	properties = c1.PropertiesJSON(500);

	// Parse JSON string into JSON objects
	root.clear();
	success = reader.parse( properties, root );
	if (!success)
		// Raise exception
		throw InvalidJSON("JSON could not be parsed (or is invalid)", "");

	try
	{
		// Check for specific things
		CHECK_CLOSE(0.0f, root["alpha"]["value"].asDouble(), 0.00001);
		CHECK_EQUAL(true, root["alpha"]["keyframe"].asBool());
		CHECK_EQUAL(true, root["changed"]["value"].asBool());

	}
	catch (exception e)
	{
		// Error parsing JSON (or missing keys)
		throw InvalidJSON("JSON is invalid (missing keys or invalid data types)", "");
	}

}

