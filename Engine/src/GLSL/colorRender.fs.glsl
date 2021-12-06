//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

// COLOR RENDER - Fragment Shader

#version 400 core

// varying
    out vec4 color;

    in VS_OUT
    {
        vec4 color;
    } fs_in;

void main(void)
{
    color = fs_in.color;
}

// --- End of File ---
