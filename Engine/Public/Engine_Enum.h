#pragma once

namespace Engine
{
	enum class STATE { RIGHT, UP, LOOK, POSITION };
	enum class PROTOTYPE { GAMEOBJECT, COMPONENT };
	enum class RENDERGROUP { RG_PRIORITY, RG_NONBLEND, RG_BLEND, RG_UI, RG_END };
	enum class WINMODE { MODE_FULL, MODE_WIN, MODE_END };

	enum class TEXTURE { RECT, CUBE };
}
