#include "olcPixelGameEngine.h"

// O------------------------------------------------------------------------------O
// | olcPixelGameEngine INTERFACE IMPLEMENTATION (CORE)                           |
// | Note: The core implementation is platform independent                        |
// O------------------------------------------------------------------------------O
namespace olc
{
	// O------------------------------------------------------------------------------O
	// | olc::Pixel IMPLEMENTATION                                                    |
	// O------------------------------------------------------------------------------O
	Pixel::Pixel()
	{
		r = 0;
		g = 0;
		b = 0;
		a = nDefaultAlpha;
	}

	Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
	{
		n = red | (green << 8) | (blue << 16) | (alpha << 24);
	} // Thanks jarekpelczar

	Pixel::Pixel(uint32_t p)
	{
		n = p;
	}

	bool Pixel::operator==(const Pixel& p) const
	{
		return n == p.n;
	}

	bool Pixel::operator!=(const Pixel& p) const
	{
		return n != p.n;
	}

	Pixel Pixel::operator *(const float i) const
	{
		float fR = std::min(255.0f, std::max(0.0f, static_cast<float>(r) * i));
		float fG = std::min(255.0f, std::max(0.0f, static_cast<float>(g) * i));
		float fB = std::min(255.0f, std::max(0.0f, static_cast<float>(b) * i));
		return Pixel(static_cast<uint8_t>(fR), static_cast<uint8_t>(fG), static_cast<uint8_t>(fB), a);
	}

	Pixel Pixel::operator /(const float i) const
	{
		float fR = std::min(255.0f, std::max(0.0f, static_cast<float>(r) / i));
		float fG = std::min(255.0f, std::max(0.0f, static_cast<float>(g) / i));
		float fB = std::min(255.0f, std::max(0.0f, static_cast<float>(b) / i));
		return Pixel(static_cast<uint8_t>(fR), static_cast<uint8_t>(fG), static_cast<uint8_t>(fB), a);
	}

	Pixel& Pixel::operator *=(const float i)
	{
		this->r = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, static_cast<float>(r) * i)));
		this->g = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, static_cast<float>(g) * i)));
		this->b = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, static_cast<float>(b) * i)));
		return *this;
	}

	Pixel& Pixel::operator /=(const float i)
	{
		this->r = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, static_cast<float>(r) / i)));
		this->g = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, static_cast<float>(g) / i)));
		this->b = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, static_cast<float>(b) / i)));
		return *this;
	}

	Pixel Pixel::operator +(const Pixel& p) const
	{
		uint8_t nR = static_cast<uint8_t>(std::min(255, std::max(0, static_cast<int>(r) + static_cast<int>(p.r))));
		uint8_t nG = static_cast<uint8_t>(std::min(255, std::max(0, static_cast<int>(g) + static_cast<int>(p.g))));
		uint8_t nB = static_cast<uint8_t>(std::min(255, std::max(0, static_cast<int>(b) + static_cast<int>(p.b))));
		return Pixel(nR, nG, nB, a);
	}

	Pixel Pixel::operator -(const Pixel& p) const
	{
		uint8_t nR = static_cast<uint8_t>(std::min(255, std::max(0, static_cast<int>(r) - static_cast<int>(p.r))));
		uint8_t nG = static_cast<uint8_t>(std::min(255, std::max(0, static_cast<int>(g) - static_cast<int>(p.g))));
		uint8_t nB = static_cast<uint8_t>(std::min(255, std::max(0, static_cast<int>(b) - static_cast<int>(p.b))));
		return Pixel(nR, nG, nB, a);
	}

	Pixel& Pixel::operator +=(const Pixel& p)
	{
		this->r = static_cast<uint8_t>(std::min(255, std::max(0, static_cast<int>(r) + static_cast<int>(p.r))));
		this->g = static_cast<uint8_t>(std::min(255, std::max(0, static_cast<int>(g) + static_cast<int>(p.g))));
		this->b = static_cast<uint8_t>(std::min(255, std::max(0, static_cast<int>(b) + static_cast<int>(p.b))));
		return *this;
	}

	Pixel& Pixel::operator -=(const Pixel& p)
	{
		this->r = static_cast<uint8_t>(std::min(255, std::max(0, static_cast<int>(r) + static_cast<int>(p.r))));
		this->g = static_cast<uint8_t>(std::min(255, std::max(0, static_cast<int>(g) + static_cast<int>(p.g))));
		this->b = static_cast<uint8_t>(std::min(255, std::max(0, static_cast<int>(b) + static_cast<int>(p.b))));
		return *this;
	}

	Pixel Pixel::inv() const
	{
		uint8_t nR = static_cast<uint8_t>(std::min(255, std::max(0, 255 - static_cast<int>(r))));
		uint8_t nG = static_cast<uint8_t>(std::min(255, std::max(0, 255 - static_cast<int>(g))));
		uint8_t nB = static_cast<uint8_t>(std::min(255, std::max(0, 255 - static_cast<int>(b))));
		return Pixel(nR, nG, nB, a);
	}

	Pixel PixelF(float red, float green, float blue, float alpha)
	{
		return Pixel(static_cast<uint8_t>(red * 255.0f), static_cast<uint8_t>(green * 255.0f),
		             static_cast<uint8_t>(blue * 255.0f), static_cast<uint8_t>(alpha * 255.0f));
	}

	Pixel PixelLerp(const Pixel& p1, const Pixel& p2, float t)
	{
		return (p1 * t) + p2 * (1.0f - t);
	}

	// O------------------------------------------------------------------------------O
	// | olc::Sprite IMPLEMENTATION                                                   |
	// O------------------------------------------------------------------------------O
	Sprite::Sprite()
	{
		pColData = nullptr;
		width = 0;
		height = 0;
	}

	Sprite::Sprite(const std::string& sImageFile, ResourcePack* pack)
	{
		LoadFromFile(sImageFile, pack);
	}

	Sprite::Sprite(int32_t w, int32_t h)
	{
		if (pColData) delete[] pColData;
		width = w;
		height = h;
		pColData = new Pixel[width * height];
		for (int32_t i = 0; i < width * height; i++)
			pColData[i] = Pixel();
	}

	Sprite::~Sprite()
	{
		if (pColData) delete[] pColData;
	}

	rcode Sprite::LoadFromPGESprFile(const std::string& sImageFile, ResourcePack* pack)
	{
		if (pColData) delete[] pColData;
		auto ReadData = [&](std::istream& is)
		{
			is.read((char*)&width, sizeof(int32_t));
			is.read((char*)&height, sizeof(int32_t));
			pColData = new Pixel[width * height];
			is.read((char*)pColData, static_cast<size_t>(width) * static_cast<size_t>(height) * sizeof(uint32_t));
		};

		// These are essentially Memory Surfaces represented by olc::Sprite
		// which load very fast, but are completely uncompressed
		if (pack == nullptr)
		{
			std::ifstream ifs;
			ifs.open(sImageFile, std::ifstream::binary);
			if (ifs.is_open())
			{
				ReadData(ifs);
				return OK;
			}
			return FAIL;
		}
		ResourceBuffer rb = pack->GetFileBuffer(sImageFile);
		std::istream is(&rb);
		ReadData(is);
		return OK;
		return FAIL;
	}

	rcode Sprite::SaveToPGESprFile(const std::string& sImageFile)
	{
		if (pColData == nullptr) return FAIL;

		std::ofstream ofs;
		ofs.open(sImageFile, std::ifstream::binary);
		if (ofs.is_open())
		{
			ofs.write((char*)&width, sizeof(int32_t));
			ofs.write((char*)&height, sizeof(int32_t));
			ofs.write((char*)pColData, static_cast<size_t>(width) * static_cast<size_t>(height) * sizeof(uint32_t));
			ofs.close();
			return OK;
		}

		return FAIL;
	}

	void Sprite::SetSampleMode(Mode mode)
	{
		modeSample = mode;
	}

	Pixel Sprite::GetPixel(const vi2d& a) const
	{
		return GetPixel(a.x, a.y);
	}

	bool Sprite::SetPixel(const vi2d& a, Pixel p)
	{
		return SetPixel(a.x, a.y, p);
	}

	Pixel Sprite::GetPixel(int32_t x, int32_t y) const
	{
		if (modeSample == NORMAL)
		{
			if (x >= 0 && x < width && y >= 0 && y < height)
				return pColData[y * width + x];
			return Pixel(0, 0, 0, 0);
		}
		return pColData[abs(y % height) * width + abs(x % width)];
	}

	bool Sprite::SetPixel(int32_t x, int32_t y, Pixel p)
	{
		if (x >= 0 && x < width && y >= 0 && y < height)
		{
			pColData[y * width + x] = p;
			return true;
		}
		return false;
	}

	Pixel Sprite::Sample(float x, float y) const
	{
		int32_t sx = std::min(static_cast<int32_t>((x * static_cast<float>(width))), width - 1);
		int32_t sy = std::min(static_cast<int32_t>((y * static_cast<float>(height))), height - 1);
		return GetPixel(sx, sy);
	}

	Pixel Sprite::SampleBL(float u, float v) const
	{
		u = u * width - 0.5f;
		v = v * height - 0.5f;
		int x = static_cast<int>(floor(u)); // cast to int rounds toward zero, not downward
		int y = static_cast<int>(floor(v)); // Thanks @joshinils
		float u_ratio = u - x;
		float v_ratio = v - y;
		float u_opposite = 1 - u_ratio;
		float v_opposite = 1 - v_ratio;

		Pixel p1 = GetPixel(std::max(x, 0), std::max(y, 0));
		Pixel p2 = GetPixel(std::min(x + 1, static_cast<int>(width) - 1), std::max(y, 0));
		Pixel p3 = GetPixel(std::max(x, 0), std::min(y + 1, static_cast<int>(height) - 1));
		Pixel p4 = GetPixel(std::min(x + 1, static_cast<int>(width) - 1), std::min(y + 1, static_cast<int>(height) - 1));

		return Pixel(
			static_cast<uint8_t>((p1.r * u_opposite + p2.r * u_ratio) * v_opposite + (p3.r * u_opposite + p4.r * u_ratio) *
				v_ratio),
			static_cast<uint8_t>((p1.g * u_opposite + p2.g * u_ratio) * v_opposite + (p3.g * u_opposite + p4.g * u_ratio) *
				v_ratio),
			static_cast<uint8_t>((p1.b * u_opposite + p2.b * u_ratio) * v_opposite + (p3.b * u_opposite + p4.b * u_ratio) *
				v_ratio));
	}

	Pixel* Sprite::GetData()
	{
		return pColData;
	}

	rcode Sprite::LoadFromFile(const std::string& sImageFile, ResourcePack* pack)
	{
		UNUSED(pack);
		return loader->LoadImageResource(this, sImageFile, pack);
	}

	Sprite* Sprite::Duplicate()
	{
		Sprite* spr = new Sprite(width, height);
		std::memcpy(spr->GetData(), GetData(), width * height * sizeof(Pixel));
		spr->modeSample = modeSample;
		return spr;
	}

	Sprite* Sprite::Duplicate(const vi2d& vPos, const vi2d& vSize)
	{
		Sprite* spr = new Sprite(vSize.x, vSize.y);
		for (int y = 0; y < vSize.y; y++)
			for (int x = 0; x < vSize.x; x++)
				spr->SetPixel(x, y, GetPixel(vPos.x + x, vPos.y + y));
		return spr;
	}

	// O------------------------------------------------------------------------------O
	// | olc::Decal IMPLEMENTATION                                                   |
	// O------------------------------------------------------------------------------O
	Decal::Decal(Sprite* spr, bool filter)
	{
		id = -1;
		if (spr == nullptr) return;
		sprite = spr;
		id = renderer->CreateTexture(sprite->width, sprite->height, filter);
		Update();
	}

	void Decal::Update()
	{
		if (sprite == nullptr) return;
		vUVScale = {1.0f / static_cast<float>(sprite->width), 1.0f / static_cast<float>(sprite->height)};
		renderer->ApplyTexture(id);
		renderer->UpdateTexture(id, sprite);
	}

	Decal::~Decal()
	{
		if (id != -1)
		{
			renderer->DeleteTexture(id);
			id = -1;
		}
	}

	void Renderable::Create(uint32_t width, uint32_t height, bool filter)
	{
		pSprite = std::make_unique<olc::Sprite>(width, height);
		pDecal = std::make_unique<olc::Decal>(pSprite.get(), filter);
	}

	rcode Renderable::Load(const std::string& sFile, ResourcePack* pack, bool filter)
	{
		pSprite = std::make_unique<olc::Sprite>();
		if (pSprite->LoadFromFile(sFile, pack) == OK)
		{
			pDecal = std::make_unique<olc::Decal>(pSprite.get(), filter);
			return OK;
		}
		pSprite.release();
		pSprite = nullptr;
		return NO_FILE;
	}

	Decal* Renderable::Decal() const
	{
		return pDecal.get();
	}

	Sprite* Renderable::Sprite() const
	{
		return pSprite.get();
	}

	// O------------------------------------------------------------------------------O
	// | olc::ResourcePack IMPLEMENTATION                                             |
	// O------------------------------------------------------------------------------O

	//=============================================================
	// Resource Packs - Allows you to store files in one large
	// scrambled file - Thanks MaGetzUb for debugging a null char in std::stringstream bug
	ResourceBuffer::ResourceBuffer(std::ifstream& ifs, uint32_t offset, uint32_t size)
	{
		vMemory.resize(size);
		ifs.seekg(offset);
		ifs.read(vMemory.data(), vMemory.size());
		setg(vMemory.data(), vMemory.data(), vMemory.data() + size);
	}

	ResourcePack::ResourcePack()
	{
	}

	ResourcePack::~ResourcePack() { baseFile.close(); }

	bool ResourcePack::AddFile(const std::string& sFile)
	{
		const std::string file = makeposix(sFile);

		if (_gfs::exists(file))
		{
			sResourceFile e;
			e.nSize = static_cast<uint32_t>(_gfs::file_size(file));
			e.nOffset = 0; // Unknown at this stage
			mapFiles[file] = e;
			return true;
		}
		return false;
	}

	bool ResourcePack::LoadPack(const std::string& sFile, const std::string& sKey)
	{
		// Open the resource file
		baseFile.open(sFile, std::ifstream::binary);
		if (!baseFile.is_open()) return false;

		// 1) Read Scrambled index
		uint32_t nIndexSize = 0;
		baseFile.read((char*)&nIndexSize, sizeof(uint32_t));

		std::vector<char> buffer(nIndexSize);
		for (uint32_t j = 0; j < nIndexSize; j++)
			buffer[j] = baseFile.get();

		std::vector<char> decoded = scramble(buffer, sKey);
		size_t pos = 0;
		auto read = [&decoded, &pos](char* dst, size_t size)
		{
			memcpy(static_cast<void*>(dst), static_cast<const void*>(decoded.data() + pos), size);
			pos += size;
		};

		auto get = [&read]() -> int
		{
			char c;
			read(&c, 1);
			return c;
		};

		// 2) Read Map
		uint32_t nMapEntries = 0;
		read((char*)&nMapEntries, sizeof(uint32_t));
		for (uint32_t i = 0; i < nMapEntries; i++)
		{
			uint32_t nFilePathSize = 0;
			read((char*)&nFilePathSize, sizeof(uint32_t));

			std::string sFileName(nFilePathSize, ' ');
			for (uint32_t j = 0; j < nFilePathSize; j++)
				sFileName[j] = get();

			sResourceFile e;
			read((char*)&e.nSize, sizeof(uint32_t));
			read((char*)&e.nOffset, sizeof(uint32_t));
			mapFiles[sFileName] = e;
		}

		// Don't close base file! we will provide a stream
		// pointer when the file is requested
		return true;
	}

	bool ResourcePack::SavePack(const std::string& sFile, const std::string& sKey)
	{
		// Create/Overwrite the resource file
		std::ofstream ofs(sFile, std::ofstream::binary);
		if (!ofs.is_open()) return false;

		// Iterate through map
		uint32_t nIndexSize = 0; // Unknown for now
		ofs.write((char*)&nIndexSize, sizeof(uint32_t));
		uint32_t nMapSize = static_cast<uint32_t>(mapFiles.size());
		ofs.write((char*)&nMapSize, sizeof(uint32_t));
		for (auto& e : mapFiles)
		{
			// Write the path of the file
			size_t nPathSize = e.first.size();
			ofs.write((char*)&nPathSize, sizeof(uint32_t));
			ofs.write(e.first.c_str(), nPathSize);

			// Write the file entry properties
			ofs.write((char*)&e.second.nSize, sizeof(uint32_t));
			ofs.write((char*)&e.second.nOffset, sizeof(uint32_t));
		}

		// 2) Write the individual Data
		std::streampos offset = ofs.tellp();
		nIndexSize = static_cast<uint32_t>(offset);
		for (auto& e : mapFiles)
		{
			// Store beginning of file offset within resource pack file
			e.second.nOffset = static_cast<uint32_t>(offset);

			// Load the file to be added
			std::vector<uint8_t> vBuffer(e.second.nSize);
			std::ifstream i(e.first, std::ifstream::binary);
			i.read((char*)vBuffer.data(), e.second.nSize);
			i.close();

			// Write the loaded file into resource pack file
			ofs.write((char*)vBuffer.data(), e.second.nSize);
			offset += e.second.nSize;
		}

		// 3) Scramble Index
		std::vector<char> stream;
		auto write = [&stream](const char* data, size_t size)
		{
			size_t sizeNow = stream.size();
			stream.resize(sizeNow + size);
			memcpy(stream.data() + sizeNow, data, size);
		};

		// Iterate through map
		write((char*)&nMapSize, sizeof(uint32_t));
		for (auto& e : mapFiles)
		{
			// Write the path of the file
			size_t nPathSize = e.first.size();
			write((char*)&nPathSize, sizeof(uint32_t));
			write(e.first.c_str(), nPathSize);

			// Write the file entry properties
			write((char*)&e.second.nSize, sizeof(uint32_t));
			write((char*)&e.second.nOffset, sizeof(uint32_t));
		}
		std::vector<char> sIndexString = scramble(stream, sKey);
		uint32_t nIndexStringLen = static_cast<uint32_t>(sIndexString.size());
		// 4) Rewrite Map (it has been updated with offsets now)
		// at start of file
		ofs.seekp(0, std::ios::beg);
		ofs.write((char*)&nIndexStringLen, sizeof(uint32_t));
		ofs.write(sIndexString.data(), nIndexStringLen);
		ofs.close();
		return true;
	}

	ResourceBuffer ResourcePack::GetFileBuffer(const std::string& sFile)
	{
		return ResourceBuffer(baseFile, mapFiles[sFile].nOffset, mapFiles[sFile].nSize);
	}

	bool ResourcePack::Loaded()
	{
		return baseFile.is_open();
	}

	std::vector<char> ResourcePack::scramble(const std::vector<char>& data, const std::string& key)
	{
		if (key.empty()) return data;
		std::vector<char> o;
		size_t c = 0;
		for (auto s : data) o.push_back(s ^ key[(c++) % key.size()]);
		return o;
	};

	std::string ResourcePack::makeposix(const std::string& path)
	{
		std::string o;
		for (auto s : path) o += std::string(1, s == '\\' ? '/' : s);
		return o;
	};

	// O------------------------------------------------------------------------------O
	// | olc::PixelGameEngine IMPLEMENTATION                                          |
	// O------------------------------------------------------------------------------O
	PixelGameEngine::PixelGameEngine()
	{
		sAppName = "Undefined";
		PGEX::pge = this;

		// Bring in relevant Platform & Rendering systems depending
		// on compiler parameters
		olc_ConfigureSystem();
	}

	PixelGameEngine::~PixelGameEngine()
	{
	}

	rcode PixelGameEngine::Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h,
	                                 bool full_screen, bool vsync, bool cohesion)
	{
		bPixelCohesion = cohesion;
		vScreenSize = {screen_w, screen_h};
		vInvScreenSize = {1.0f / static_cast<float>(screen_w), 1.0f / static_cast<float>(screen_h)};
		vPixelSize = {pixel_w, pixel_h};
		vWindowSize = vScreenSize * vPixelSize;
		bFullScreen = full_screen;
		bEnableVSYNC = vsync;
		vPixel = 2.0f / vScreenSize;

		if (vPixelSize.x <= 0 || vPixelSize.y <= 0 || vScreenSize.x <= 0 || vScreenSize.y <= 0)
			return FAIL;

		return OK;
	}

	void PixelGameEngine::SetScreenSize(int w, int h)
	{
		vScreenSize = {w, h};
		vInvScreenSize = {1.0f / static_cast<float>(w), 1.0f / static_cast<float>(h)};
		for (auto& layer : vLayers)
		{
			delete layer.pDrawTarget; // Erase existing layer sprites
			layer.pDrawTarget = new Sprite(vScreenSize.x, vScreenSize.y);
			layer.bUpdate = true;
		}
		SetDrawTarget(nullptr);

		renderer->ClearBuffer(BLACK, true);
		renderer->DisplayFrame();
		renderer->ClearBuffer(BLACK, true);
		renderer->UpdateViewport(vViewPos, vViewSize);
	}

#if !defined(PGE_USE_CUSTOM_START)
	rcode PixelGameEngine::Start()
	{
		if (platform->ApplicationStartUp() != OK) return FAIL;

		// Construct the window
		if (platform->CreateWindowPane({30, 30}, vWindowSize, bFullScreen) != OK) return FAIL;
		olc_UpdateWindowSize(vWindowSize.x, vWindowSize.y);

		// Start the thread
		bAtomActive = true;
		std::thread t = std::thread(&PixelGameEngine::EngineThread, this);

		// Some implementations may form an event loop here
		platform->StartSystemEventLoop();

		// Wait for thread to be exited
		t.join();

		if (platform->ApplicationCleanUp() != OK) return FAIL;

		return OK;
	}
#endif

	void PixelGameEngine::SetDrawTarget(Sprite* target)
	{
		if (target)
		{
			pDrawTarget = target;
		}
		else
		{
			nTargetLayer = 0;
			pDrawTarget = vLayers[0].pDrawTarget;
		}
	}

	void PixelGameEngine::SetDrawTarget(uint8_t layer)
	{
		if (layer < vLayers.size())
		{
			pDrawTarget = vLayers[layer].pDrawTarget;
			vLayers[layer].bUpdate = true;
			nTargetLayer = layer;
		}
	}

	void PixelGameEngine::EnableLayer(uint8_t layer, bool b)
	{
		if (layer < vLayers.size()) vLayers[layer].bShow = b;
	}

	void PixelGameEngine::SetLayerOffset(uint8_t layer, const vf2d& offset)
	{
		SetLayerOffset(layer, offset.x, offset.y);
	}

	void PixelGameEngine::SetLayerOffset(uint8_t layer, float x, float y)
	{
		if (layer < vLayers.size()) vLayers[layer].vOffset = {x, y};
	}

	void PixelGameEngine::SetLayerScale(uint8_t layer, const vf2d& scale)
	{
		SetLayerScale(layer, scale.x, scale.y);
	}

	void PixelGameEngine::SetLayerScale(uint8_t layer, float x, float y)
	{
		if (layer < vLayers.size()) vLayers[layer].vScale = {x, y};
	}

	void PixelGameEngine::SetLayerTint(uint8_t layer, const Pixel& tint)
	{
		if (layer < vLayers.size()) vLayers[layer].tint = tint;
	}

	void PixelGameEngine::SetLayerCustomRenderFunction(uint8_t layer, std::function<void()> f)
	{
		if (layer < vLayers.size()) vLayers[layer].funcHook = f;
	}

	std::vector<LayerDesc>& PixelGameEngine::GetLayers()
	{
		return vLayers;
	}

	uint32_t PixelGameEngine::CreateLayer()
	{
		LayerDesc ld;
		ld.pDrawTarget = new Sprite(vScreenSize.x, vScreenSize.y);
		ld.nResID = renderer->CreateTexture(vScreenSize.x, vScreenSize.y);
		renderer->UpdateTexture(ld.nResID, ld.pDrawTarget);
		vLayers.push_back(ld);
		return static_cast<uint32_t>(vLayers.size()) - 1;
	}

	Sprite* PixelGameEngine::GetDrawTarget() const
	{
		return pDrawTarget;
	}

	int32_t PixelGameEngine::GetDrawTargetWidth() const
	{
		if (pDrawTarget)
			return pDrawTarget->width;
		return 0;
	}

	int32_t PixelGameEngine::GetDrawTargetHeight() const
	{
		if (pDrawTarget)
			return pDrawTarget->height;
		return 0;
	}

	uint32_t PixelGameEngine::GetFPS() const
	{
		return nLastFPS;
	}

	bool PixelGameEngine::IsFocused() const
	{
		return bHasInputFocus;
	}

	HWButton PixelGameEngine::GetKey(Key k) const
	{
		return pKeyboardState[k];
	}

	HWButton PixelGameEngine::GetMouse(uint32_t b) const
	{
		return pMouseState[b];
	}

	int32_t PixelGameEngine::GetMouseX() const
	{
		return vMousePos.x;
	}

	int32_t PixelGameEngine::GetMouseY() const
	{
		return vMousePos.y;
	}

	const vi2d& PixelGameEngine::GetMousePos() const
	{
		return vMousePos;
	}

	int32_t PixelGameEngine::GetMouseWheel() const
	{
		return nMouseWheelDelta;
	}

	int32_t PixelGameEngine::ScreenWidth() const
	{
		return vScreenSize.x;
	}

	int32_t PixelGameEngine::ScreenHeight() const
	{
		return vScreenSize.y;
	}

	float PixelGameEngine::GetElapsedTime() const
	{
		return fLastElapsed;
	}

	const vi2d& PixelGameEngine::GetWindowSize() const
	{
		return vWindowSize;
	}

	const vi2d& PixelGameEngine::GetPixelSize() const
	{
		return vPixelSize;
	}

	const vi2d& PixelGameEngine::GetScreenPixelSize() const
	{
		return vScreenPixelSize;
	}

	const vi2d& PixelGameEngine::GetWindowMouse() const
	{
		return vMouseWindowPos;
	}

	bool PixelGameEngine::Draw(const vi2d& pos, Pixel p)
	{
		return Draw(pos.x, pos.y, p);
	}

	// This is it, the critical function that plots a pixel
	bool PixelGameEngine::Draw(int32_t x, int32_t y, Pixel p)
	{
		if (!pDrawTarget) return false;

		if (nPixelMode == Pixel::NORMAL)
		{
			return pDrawTarget->SetPixel(x, y, p);
		}

		if (nPixelMode == Pixel::MASK)
		{
			if (p.a == 255)
				return pDrawTarget->SetPixel(x, y, p);
		}

		if (nPixelMode == Pixel::ALPHA)
		{
			Pixel d = pDrawTarget->GetPixel(x, y);
			float a = static_cast<float>(p.a / 255.0f) * fBlendFactor;
			float c = 1.0f - a;
			float r = a * static_cast<float>(p.r) + c * static_cast<float>(d.r);
			float g = a * static_cast<float>(p.g) + c * static_cast<float>(d.g);
			float b = a * static_cast<float>(p.b) + c * static_cast<float>(d.b);
			return pDrawTarget->SetPixel(x, y, Pixel(static_cast<uint8_t>(r), static_cast<uint8_t>(g),
			                                         static_cast<uint8_t>(b)/*, (uint8_t)(p.a * fBlendFactor)*/));
		}

		if (nPixelMode == Pixel::CUSTOM)
		{
			return pDrawTarget->SetPixel(x, y, funcPixelMode(x, y, p, pDrawTarget->GetPixel(x, y)));
		}

		return false;
	}

	void PixelGameEngine::DrawLine(const vi2d& pos1, const vi2d& pos2, Pixel p, uint32_t pattern)
	{
		DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, p, pattern);
	}

	void PixelGameEngine::DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Pixel p, uint32_t pattern)
	{
		int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
		dx = x2 - x1;
		dy = y2 - y1;

		auto rol = [&](void)
		{
			pattern = (pattern << 1) | (pattern >> 31);
			return pattern & 1;
		};

		// straight lines idea by gurkanctn
		if (dx == 0) // Line is vertical
		{
			if (y2 < y1) std::swap(y1, y2);
			for (y = y1; y <= y2; y++) if (rol()) Draw(x1, y, p);
			return;
		}

		if (dy == 0) // Line is horizontal
		{
			if (x2 < x1) std::swap(x1, x2);
			for (x = x1; x <= x2; x++) if (rol()) Draw(x, y1, p);
			return;
		}

		// Line is Funk-aye
		dx1 = abs(dx);
		dy1 = abs(dy);
		px = 2 * dy1 - dx1;
		py = 2 * dx1 - dy1;
		if (dy1 <= dx1)
		{
			if (dx >= 0)
			{
				x = x1;
				y = y1;
				xe = x2;
			}
			else
			{
				x = x2;
				y = y2;
				xe = x1;
			}

			if (rol()) Draw(x, y, p);

			for (i = 0; x < xe; i++)
			{
				x = x + 1;
				if (px < 0)
					px = px + 2 * dy1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1;
					else y = y - 1;
					px = px + 2 * (dy1 - dx1);
				}
				if (rol()) Draw(x, y, p);
			}
		}
		else
		{
			if (dy >= 0)
			{
				x = x1;
				y = y1;
				ye = y2;
			}
			else
			{
				x = x2;
				y = y2;
				ye = y1;
			}

			if (rol()) Draw(x, y, p);

			for (i = 0; y < ye; i++)
			{
				y = y + 1;
				if (py <= 0)
					py = py + 2 * dx1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1;
					else x = x - 1;
					py = py + 2 * (dx1 - dy1);
				}
				if (rol()) Draw(x, y, p);
			}
		}
	}

	void PixelGameEngine::DrawCircle(const vi2d& pos, int32_t radius, Pixel p, uint8_t mask)
	{
		DrawCircle(pos.x, pos.y, radius, p, mask);
	}

	void PixelGameEngine::DrawCircle(int32_t x, int32_t y, int32_t radius, Pixel p, uint8_t mask)
	{
		// Thanks to IanM-Matrix1 #PR121
		if (radius < 0 || x < -radius || y < -radius || x - GetDrawTargetWidth() > radius || y - GetDrawTargetHeight() >
			radius)
			return;

		if (radius > 0)
		{
			int x0 = 0;
			int y0 = radius;
			int d = 3 - 2 * radius;

			while (y0 >= x0) // only formulate 1/8 of circle
			{
				// Draw even octants
				if (mask & 0x01) Draw(x + x0, y - y0, p); // Q6 - upper right right
				if (mask & 0x04) Draw(x + y0, y + x0, p); // Q4 - lower lower right
				if (mask & 0x10) Draw(x - x0, y + y0, p); // Q2 - lower left left
				if (mask & 0x40) Draw(x - y0, y - x0, p); // Q0 - upper upper left
				if (x0 != 0 && x0 != y0)
				{
					if (mask & 0x02) Draw(x + y0, y - x0, p); // Q7 - upper upper right
					if (mask & 0x08) Draw(x + x0, y + y0, p); // Q5 - lower right right
					if (mask & 0x20) Draw(x - y0, y + x0, p); // Q3 - lower lower left
					if (mask & 0x80) Draw(x - x0, y - y0, p); // Q1 - upper left left
				}

				if (d < 0)
					d += 4 * x0++ + 6;
				else
					d += 4 * (x0++ - y0--) + 10;
			}
		}
		else
			Draw(x, y, p);
	}

	void PixelGameEngine::FillCircle(const vi2d& pos, int32_t radius, Pixel p)
	{
		FillCircle(pos.x, pos.y, radius, p);
	}

	void PixelGameEngine::FillCircle(int32_t x, int32_t y, int32_t radius, Pixel p)
	{
		// Thanks to IanM-Matrix1 #PR121
		if (radius < 0 || x < -radius || y < -radius || x - GetDrawTargetWidth() > radius || y - GetDrawTargetHeight() >
			radius)
			return;

		if (radius > 0)
		{
			int x0 = 0;
			int y0 = radius;
			int d = 3 - 2 * radius;

			auto drawline = [&](int sx, int ex, int y)
			{
				for (int x = sx; x <= ex; x++)
					Draw(x, y, p);
			};

			while (y0 >= x0)
			{
				drawline(x - y0, x + y0, y - x0);
				if (x0 > 0) drawline(x - y0, x + y0, y + x0);

				if (d < 0)
					d += 4 * x0++ + 6;
				else
				{
					if (x0 != y0)
					{
						drawline(x - x0, x + x0, y - y0);
						drawline(x - x0, x + x0, y + y0);
					}
					d += 4 * (x0++ - y0--) + 10;
				}
			}
		}
		else
			Draw(x, y, p);
	}

	void PixelGameEngine::DrawRect(const vi2d& pos, const vi2d& size, Pixel p)
	{
		DrawRect(pos.x, pos.y, size.x, size.y, p);
	}

	void PixelGameEngine::DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p)
	{
		DrawLine(x, y, x + w, y, p);
		DrawLine(x + w, y, x + w, y + h, p);
		DrawLine(x + w, y + h, x, y + h, p);
		DrawLine(x, y + h, x, y, p);
	}

	void PixelGameEngine::Clear(Pixel p)
	{
		int pixels = GetDrawTargetWidth() * GetDrawTargetHeight();
		Pixel* m = GetDrawTarget()->GetData();
		for (int i = 0; i < pixels; i++) m[i] = p;
	}

	void PixelGameEngine::ClearBuffer(Pixel p, bool bDepth)
	{
		renderer->ClearBuffer(p, bDepth);
	}

	void PixelGameEngine::FillRect(const vi2d& pos, const vi2d& size, Pixel p)
	{
		FillRect(pos.x, pos.y, size.x, size.y, p);
	}

	void PixelGameEngine::FillRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p)
	{
		int32_t x2 = x + w;
		int32_t y2 = y + h;

		if (x < 0) x = 0;
		if (x >= static_cast<int32_t>(GetDrawTargetWidth())) x = static_cast<int32_t>(GetDrawTargetWidth());
		if (y < 0) y = 0;
		if (y >= static_cast<int32_t>(GetDrawTargetHeight())) y = static_cast<int32_t>(GetDrawTargetHeight());

		if (x2 < 0) x2 = 0;
		if (x2 >= static_cast<int32_t>(GetDrawTargetWidth())) x2 = static_cast<int32_t>(GetDrawTargetWidth());
		if (y2 < 0) y2 = 0;
		if (y2 >= static_cast<int32_t>(GetDrawTargetHeight())) y2 = static_cast<int32_t>(GetDrawTargetHeight());

		for (int i = x; i < x2; i++)
			for (int j = y; j < y2; j++)
				Draw(i, j, p);
	}

	void PixelGameEngine::DrawTriangle(const vi2d& pos1, const vi2d& pos2, const vi2d& pos3, Pixel p)
	{
		DrawTriangle(pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y, p);
	}

	void PixelGameEngine::DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p)
	{
		DrawLine(x1, y1, x2, y2, p);
		DrawLine(x2, y2, x3, y3, p);
		DrawLine(x3, y3, x1, y1, p);
	}

	void PixelGameEngine::FillTriangle(const vi2d& pos1, const vi2d& pos2, const vi2d& pos3, Pixel p)
	{
		FillTriangle(pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y, p);
	}

	// https://www.avrfreaks.net/sites/default/files/triangles.c
	void PixelGameEngine::FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p)
	{
		auto drawline = [&](int sx, int ex, int ny) { for (int i = sx; i <= ex; i++) Draw(i, ny, p); };

		int t1x, t2x, y, minx, maxx, t1xp, t2xp;
		bool changed1 = false;
		bool changed2 = false;
		int signx1, signx2, dx1, dy1, dx2, dy2;
		int e1, e2;
		// Sort vertices
		if (y1 > y2)
		{
			std::swap(y1, y2);
			std::swap(x1, x2);
		}
		if (y1 > y3)
		{
			std::swap(y1, y3);
			std::swap(x1, x3);
		}
		if (y2 > y3)
		{
			std::swap(y2, y3);
			std::swap(x2, x3);
		}

		t1x = t2x = x1;
		y = y1; // Starting points
		dx1 = static_cast<int>(x2 - x1);
		if (dx1 < 0)
		{
			dx1 = -dx1;
			signx1 = -1;
		}
		else signx1 = 1;
		dy1 = static_cast<int>(y2 - y1);

		dx2 = static_cast<int>(x3 - x1);
		if (dx2 < 0)
		{
			dx2 = -dx2;
			signx2 = -1;
		}
		else signx2 = 1;
		dy2 = static_cast<int>(y3 - y1);

		if (dy1 > dx1)
		{
			std::swap(dx1, dy1);
			changed1 = true;
		}
		if (dy2 > dx2)
		{
			std::swap(dy2, dx2);
			changed2 = true;
		}

		e2 = static_cast<int>(dx2 >> 1);
		// Flat top, just process the second half
		if (y1 == y2) goto next;
		e1 = static_cast<int>(dx1 >> 1);

		for (int i = 0; i < dx1;)
		{
			t1xp = 0;
			t2xp = 0;
			if (t1x < t2x)
			{
				minx = t1x;
				maxx = t2x;
			}
			else
			{
				minx = t2x;
				maxx = t1x;
			}
			// process first line until y value is about to change
			while (i < dx1)
			{
				i++;
				e1 += dy1;
				while (e1 >= dx1)
				{
					e1 -= dx1;
					if (changed1) t1xp = signx1; //t1x += signx1;
					else goto next1;
				}
				if (changed1) break;
				t1x += signx1;
			}
			// Move line
		next1:
			// process second line until y value is about to change
			while (true)
			{
				e2 += dy2;
				while (e2 >= dx2)
				{
					e2 -= dx2;
					if (changed2) t2xp = signx2; //t2x += signx2;
					else goto next2;
				}
				if (changed2) break;
				t2x += signx2;
			}
		next2:
			if (minx > t1x) minx = t1x;
			if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x;
			if (maxx < t2x) maxx = t2x;
			drawline(minx, maxx, y); // Draw line from min to max points found on the y
			// Now increase y
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y == y2) break;
		}
	next:
		// Second half
		dx1 = static_cast<int>(x3 - x2);
		if (dx1 < 0)
		{
			dx1 = -dx1;
			signx1 = -1;
		}
		else signx1 = 1;
		dy1 = static_cast<int>(y3 - y2);
		t1x = x2;

		if (dy1 > dx1)
		{
			// swap values
			std::swap(dy1, dx1);
			changed1 = true;
		}
		else changed1 = false;

		e1 = static_cast<int>(dx1 >> 1);

		for (int i = 0; i <= dx1; i++)
		{
			t1xp = 0;
			t2xp = 0;
			if (t1x < t2x)
			{
				minx = t1x;
				maxx = t2x;
			}
			else
			{
				minx = t2x;
				maxx = t1x;
			}
			// process first line until y value is about to change
			while (i < dx1)
			{
				e1 += dy1;
				while (e1 >= dx1)
				{
					e1 -= dx1;
					if (changed1)
					{
						t1xp = signx1;
						break;
					} //t1x += signx1;
					goto next3;
				}
				if (changed1) break;
				t1x += signx1;
				if (i < dx1) i++;
			}
		next3:
			// process second line until y value is about to change
			while (t2x != x3)
			{
				e2 += dy2;
				while (e2 >= dx2)
				{
					e2 -= dx2;
					if (changed2) t2xp = signx2;
					else goto next4;
				}
				if (changed2) break;
				t2x += signx2;
			}
		next4:

			if (minx > t1x) minx = t1x;
			if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x;
			if (maxx < t2x) maxx = t2x;
			drawline(minx, maxx, y);
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y > y3) return;
		}
	}

	void PixelGameEngine::DrawSprite(const vi2d& pos, Sprite* sprite, uint32_t scale, uint8_t flip)
	{
		DrawSprite(pos.x, pos.y, sprite, scale, flip);
	}

	void PixelGameEngine::DrawSprite(int32_t x, int32_t y, Sprite* sprite, uint32_t scale, uint8_t flip)
	{
		if (sprite == nullptr)
			return;

		int32_t fxs = 0, fxm = 1, fx = 0;
		int32_t fys = 0, fym = 1, fy = 0;
		if (flip & Sprite::Flip::HORIZ)
		{
			fxs = sprite->width - 1;
			fxm = -1;
		}
		if (flip & Sprite::Flip::VERT)
		{
			fys = sprite->height - 1;
			fym = -1;
		}

		if (scale > 1)
		{
			fx = fxs;
			for (int32_t i = 0; i < sprite->width; i++, fx += fxm)
			{
				fy = fys;
				for (int32_t j = 0; j < sprite->height; j++, fy += fym)
					for (uint32_t is = 0; is < scale; is++)
						for (uint32_t js = 0; js < scale; js++)
							Draw(x + (i * scale) + is, y + (j * scale) + js, sprite->GetPixel(fx, fy));
			}
		}
		else
		{
			fx = fxs;
			for (int32_t i = 0; i < sprite->width; i++, fx += fxm)
			{
				fy = fys;
				for (int32_t j = 0; j < sprite->height; j++, fy += fym)
					Draw(x + i, y + j, sprite->GetPixel(fx, fy));
			}
		}
	}

	void PixelGameEngine::DrawPartialSprite(const vi2d& pos, Sprite* sprite, const vi2d& sourcepos, const vi2d& size,
	                                        uint32_t scale, uint8_t flip)
	{
		DrawPartialSprite(pos.x, pos.y, sprite, sourcepos.x, sourcepos.y, size.x, size.y, scale, flip);
	}

	void PixelGameEngine::DrawPartialSprite(int32_t x, int32_t y, Sprite* sprite, int32_t ox, int32_t oy, int32_t w,
	                                        int32_t h, uint32_t scale, uint8_t flip)
	{
		if (sprite == nullptr)
			return;

		int32_t fxs = 0, fxm = 1, fx = 0;
		int32_t fys = 0, fym = 1, fy = 0;
		if (flip & Sprite::Flip::HORIZ)
		{
			fxs = w - 1;
			fxm = -1;
		}
		if (flip & Sprite::Flip::VERT)
		{
			fys = h - 1;
			fym = -1;
		}

		if (scale > 1)
		{
			fx = fxs;
			for (int32_t i = 0; i < w; i++, fx += fxm)
			{
				fy = fys;
				for (int32_t j = 0; j < h; j++, fy += fym)
					for (uint32_t is = 0; is < scale; is++)
						for (uint32_t js = 0; js < scale; js++)
							Draw(x + (i * scale) + is, y + (j * scale) + js, sprite->GetPixel(fx + ox, fy + oy));
			}
		}
		else
		{
			fx = fxs;
			for (int32_t i = 0; i < w; i++, fx += fxm)
			{
				fy = fys;
				for (int32_t j = 0; j < h; j++, fy += fym)
					Draw(x + i, y + j, sprite->GetPixel(fx + ox, fy + oy));
			}
		}
	}

	void PixelGameEngine::SetDecalMode(const DecalMode& mode)
	{
		nDecalMode = mode;
	}

	void PixelGameEngine::DrawPartialDecal(const vf2d& pos, Decal* decal, const vf2d& source_pos, const vf2d& source_size,
	                                       const
	                                       vf2d& scale, const Pixel& tint)
	{
		vf2d vScreenSpacePos =
		{
			(pos.x * vInvScreenSize.x) * 2.0f - 1.0f,
			((pos.y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f
		};

		vf2d vScreenSpaceDim =
		{
			vScreenSpacePos.x + (2.0f * source_size.x * vInvScreenSize.x) * scale.x,
			vScreenSpacePos.y - (2.0f * source_size.y * vInvScreenSize.y) * scale.y
		};

		DecalInstance di;
		di.decal = decal;
		di.tint[0] = tint;

		di.pos[0] = {vScreenSpacePos.x, vScreenSpacePos.y};
		di.pos[1] = {vScreenSpacePos.x, vScreenSpaceDim.y};
		di.pos[2] = {vScreenSpaceDim.x, vScreenSpaceDim.y};
		di.pos[3] = {vScreenSpaceDim.x, vScreenSpacePos.y};

		vf2d uvtl = source_pos * decal->vUVScale;
		vf2d uvbr = uvtl + (source_size * decal->vUVScale);
		di.uv[0] = {uvtl.x, uvtl.y};
		di.uv[1] = {uvtl.x, uvbr.y};
		di.uv[2] = {uvbr.x, uvbr.y};
		di.uv[3] = {uvbr.x, uvtl.y};
		di.mode = nDecalMode;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawPartialDecal(const vf2d& pos, const vf2d& size, Decal* decal, const vf2d& source_pos, const
	                                       vf2d& source_size, const Pixel& tint)
	{
		vf2d vScreenSpacePos =
		{
			(pos.x * vInvScreenSize.x) * 2.0f - 1.0f,
			((pos.y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f
		};

		vf2d vScreenSpaceDim =
		{
			vScreenSpacePos.x + (2.0f * size.x * vInvScreenSize.x),
			vScreenSpacePos.y - (2.0f * size.y * vInvScreenSize.y)
		};

		DecalInstance di;
		di.decal = decal;
		di.tint[0] = tint;

		di.pos[0] = {vScreenSpacePos.x, vScreenSpacePos.y};
		di.pos[1] = {vScreenSpacePos.x, vScreenSpaceDim.y};
		di.pos[2] = {vScreenSpaceDim.x, vScreenSpaceDim.y};
		di.pos[3] = {vScreenSpaceDim.x, vScreenSpacePos.y};

		vf2d uvtl = source_pos * decal->vUVScale;
		vf2d uvbr = uvtl + (source_size * decal->vUVScale);
		di.uv[0] = {uvtl.x, uvtl.y};
		di.uv[1] = {uvtl.x, uvbr.y};
		di.uv[2] = {uvbr.x, uvbr.y};
		di.uv[3] = {uvbr.x, uvtl.y};
		di.mode = nDecalMode;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawDecal(const vf2d& pos, Decal* decal, const vf2d& scale, const Pixel& tint)
	{
		vf2d vScreenSpacePos =
		{
			(pos.x * vInvScreenSize.x) * 2.0f - 1.0f,
			((pos.y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f
		};

		vf2d vScreenSpaceDim =
		{
			vScreenSpacePos.x + (2.0f * (static_cast<float>(decal->sprite->width) * vInvScreenSize.x)) * scale.x,
			vScreenSpacePos.y - (2.0f * (static_cast<float>(decal->sprite->height) * vInvScreenSize.y)) * scale.y
		};

		DecalInstance di;
		di.decal = decal;
		di.tint[0] = tint;
		di.pos[0] = {vScreenSpacePos.x, vScreenSpacePos.y};
		di.pos[1] = {vScreenSpacePos.x, vScreenSpaceDim.y};
		di.pos[2] = {vScreenSpaceDim.x, vScreenSpaceDim.y};
		di.pos[3] = {vScreenSpaceDim.x, vScreenSpacePos.y};
		di.mode = nDecalMode;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawRotatedDecal(const vf2d& pos, Decal* decal, const float fAngle, const vf2d& center, const
	                                       vf2d& scale, const Pixel& tint)
	{
		DecalInstance di;
		di.decal = decal;
		di.tint[0] = tint;
		di.pos[0] = (vf2d(0.0f, 0.0f) - center) * scale;
		di.pos[1] = (vf2d(0.0f, static_cast<float>(decal->sprite->height)) - center) * scale;
		di.pos[2] = (vf2d(static_cast<float>(decal->sprite->width), static_cast<float>(decal->sprite->height)) - center) *
			scale;
		di.pos[3] = (vf2d(static_cast<float>(decal->sprite->width), 0.0f) - center) * scale;
		float c = cos(fAngle), s = sin(fAngle);
		for (int i = 0; i < 4; i++)
		{
			di.pos[i] = pos + vf2d(di.pos[i].x * c - di.pos[i].y * s, di.pos[i].x * s + di.pos[i].y * c);
			di.pos[i] = di.pos[i] * vInvScreenSize * 2.0f - vf2d(1.0f, 1.0f);
			di.pos[i].y *= -1.0f;
		}
		di.mode = nDecalMode;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawExplicitDecal(Decal* decal, const vf2d* pos, const vf2d* uv, const Pixel* col)
	{
		DecalInstance di;
		di.decal = decal;
		for (int i = 0; i < 4; i++)
		{
			di.pos[i] = {(pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f};
			di.uv[i] = uv[i];
			di.tint[i] = col[i];
		}
		di.mode = nDecalMode;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::FillRectDecal(const vf2d& pos, const vf2d& size, const Pixel col)
	{
		std::array<vf2d, 4> points = {{{pos}, {pos.x, pos.y + size.y}, {pos + size}, {pos.x + size.x, pos.y}}};
		std::array<vf2d, 4> uvs = {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}};
		std::array<Pixel, 4> cols = {{col, col, col, col}};
		DrawExplicitDecal(nullptr, points.data(), uvs.data(), cols.data());
	}

	void PixelGameEngine::GradientFillRectDecal(const vf2d& pos, const vf2d& size, const Pixel colTL, const Pixel colBL,
	                                            const
	                                            Pixel colBR, const Pixel colTR)
	{
		std::array<vf2d, 4> points = {{{pos}, {pos.x, pos.y + size.y}, {pos + size}, {pos.x + size.x, pos.y}}};
		std::array<vf2d, 4> uvs = {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}};
		std::array<Pixel, 4> cols = {{colTL, colBL, colBR, colTR}};
		DrawExplicitDecal(nullptr, points.data(), uvs.data(), cols.data());
	}

	void PixelGameEngine::DrawPartialRotatedDecal(const vf2d& pos, Decal* decal, const float fAngle, const vf2d& center,
	                                              const
	                                              vf2d& source_pos, const vf2d& source_size, const vf2d& scale, const
	                                              Pixel& tint)
	{
		DecalInstance di;
		di.decal = decal;
		di.tint[0] = tint;
		di.pos[0] = (vf2d(0.0f, 0.0f) - center) * scale;
		di.pos[1] = (vf2d(0.0f, source_size.y) - center) * scale;
		di.pos[2] = (vf2d(source_size.x, source_size.y) - center) * scale;
		di.pos[3] = (vf2d(source_size.x, 0.0f) - center) * scale;
		float c = cos(fAngle), s = sin(fAngle);
		for (int i = 0; i < 4; i++)
		{
			di.pos[i] = pos + vf2d(di.pos[i].x * c - di.pos[i].y * s, di.pos[i].x * s + di.pos[i].y * c);
			di.pos[i] = di.pos[i] * vInvScreenSize * 2.0f - vf2d(1.0f, 1.0f);
			di.pos[i].y *= -1.0f;
		}

		vf2d uvtl = source_pos * decal->vUVScale;
		vf2d uvbr = uvtl + (source_size * decal->vUVScale);
		di.uv[0] = {uvtl.x, uvtl.y};
		di.uv[1] = {uvtl.x, uvbr.y};
		di.uv[2] = {uvbr.x, uvbr.y};
		di.uv[3] = {uvbr.x, uvtl.y};
		di.mode = nDecalMode;
		vLayers[nTargetLayer].vecDecalInstance.push_back(di);
	}

	void PixelGameEngine::DrawPartialWarpedDecal(Decal* decal, const vf2d* pos, const vf2d& source_pos,
	                                             const vf2d& source_size, const
	                                             Pixel& tint)
	{
		DecalInstance di;
		di.decal = decal;
		di.tint[0] = tint;
		vf2d center;
		float rd = ((pos[2].x - pos[0].x) * (pos[3].y - pos[1].y) - (pos[3].x - pos[1].x) * (pos[2].y - pos[0].y));
		if (rd != 0)
		{
			vf2d uvtl = source_pos * decal->vUVScale;
			vf2d uvbr = uvtl + (source_size * decal->vUVScale);
			di.uv[0] = {uvtl.x, uvtl.y};
			di.uv[1] = {uvtl.x, uvbr.y};
			di.uv[2] = {uvbr.x, uvbr.y};
			di.uv[3] = {uvbr.x, uvtl.y};

			rd = 1.0f / rd;
			float rn = ((pos[3].x - pos[1].x) * (pos[0].y - pos[1].y) - (pos[3].y - pos[1].y) * (pos[0].x - pos[1].x)) * rd;
			float sn = ((pos[2].x - pos[0].x) * (pos[0].y - pos[1].y) - (pos[2].y - pos[0].y) * (pos[0].x - pos[1].x)) * rd;
			if (!(rn < 0.f || rn > 1.f || sn < 0.f || sn > 1.f)) center = pos[0] + rn * (pos[2] - pos[0]);
			float d[4];
			for (int i = 0; i < 4; i++) d[i] = (pos[i] - center).mag();
			for (int i = 0; i < 4; i++)
			{
				float q = d[i] == 0.0f ? 1.0f : (d[i] + d[(i + 2) & 3]) / d[(i + 2) & 3];
				di.uv[i] *= q;
				di.w[i] *= q;
				di.pos[i] = {
					(pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f
				};
			}
			di.mode = nDecalMode;
			vLayers[nTargetLayer].vecDecalInstance.push_back(di);
		}
	}

	void PixelGameEngine::DrawWarpedDecal(Decal* decal, const vf2d* pos, const Pixel& tint)
	{
		// Thanks Nathan Reed, a brilliant article explaining whats going on here
		// http://www.reedbeta.com/blog/quadrilateral-interpolation-part-1/
		DecalInstance di;
		di.decal = decal;
		di.tint[0] = tint;
		vf2d center;
		float rd = ((pos[2].x - pos[0].x) * (pos[3].y - pos[1].y) - (pos[3].x - pos[1].x) * (pos[2].y - pos[0].y));
		if (rd != 0)
		{
			rd = 1.0f / rd;
			float rn = ((pos[3].x - pos[1].x) * (pos[0].y - pos[1].y) - (pos[3].y - pos[1].y) * (pos[0].x - pos[1].x)) * rd;
			float sn = ((pos[2].x - pos[0].x) * (pos[0].y - pos[1].y) - (pos[2].y - pos[0].y) * (pos[0].x - pos[1].x)) * rd;
			if (!(rn < 0.f || rn > 1.f || sn < 0.f || sn > 1.f)) center = pos[0] + rn * (pos[2] - pos[0]);
			float d[4];
			for (int i = 0; i < 4; i++) d[i] = (pos[i] - center).mag();
			for (int i = 0; i < 4; i++)
			{
				float q = d[i] == 0.0f ? 1.0f : (d[i] + d[(i + 2) & 3]) / d[(i + 2) & 3];
				di.uv[i] *= q;
				di.w[i] *= q;
				di.pos[i] = {
					(pos[i].x * vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f
				};
			}
			di.mode = nDecalMode;
			vLayers[nTargetLayer].vecDecalInstance.push_back(di);
		}
	}

	void PixelGameEngine::DrawWarpedDecal(Decal* decal, const std::array<vf2d, 4>& pos, const Pixel& tint)
	{
		DrawWarpedDecal(decal, pos.data(), tint);
	}

	void PixelGameEngine::DrawWarpedDecal(Decal* decal, const vf2d (&pos)[4], const Pixel& tint)
	{
		DrawWarpedDecal(decal, &pos[0], tint);
	}

	void PixelGameEngine::DrawPartialWarpedDecal(Decal* decal, const std::array<vf2d, 4>& pos, const vf2d& source_pos,
	                                             const
	                                             vf2d& source_size, const Pixel& tint)
	{
		DrawPartialWarpedDecal(decal, pos.data(), source_pos, source_size, tint);
	}

	void PixelGameEngine::DrawPartialWarpedDecal(Decal* decal, const vf2d (&pos)[4], const vf2d& source_pos,
	                                             const vf2d& source_size, const
	                                             Pixel& tint)
	{
		DrawPartialWarpedDecal(decal, &pos[0], source_pos, source_size, tint);
	}

	void PixelGameEngine::DrawStringDecal(const vf2d& pos, const std::string& sText, const Pixel col, const vf2d& scale)
	{
		vf2d spos = {0.0f, 0.0f};
		for (auto c : sText)
		{
			if (c == '\n')
			{
				spos.x = 0;
				spos.y += 8.0f * scale.y;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;
				DrawPartialDecal(pos + spos, fontDecal, {static_cast<float>(ox) * 8.0f, static_cast<float>(oy) * 8.0f},
				                 {8.0f, 8.0f}, scale, col);
				spos.x += 8.0f * scale.x;
			}
		}
	}

	void PixelGameEngine::DrawStringPropDecal(const vf2d& pos, const std::string& sText, const Pixel col,
	                                          const vf2d& scale)
	{
		vf2d spos = {0.0f, 0.0f};
		for (auto c : sText)
		{
			if (c == '\n')
			{
				spos.x = 0;
				spos.y += 8.0f * scale.y;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;
				DrawPartialDecal(pos + spos, fontDecal,
				                 {
					                 static_cast<float>(ox) * 8.0f + static_cast<float>(vFontSpacing[c - 32].x),
					                 static_cast<float>(oy) * 8.0f
				                 }, {static_cast<float>(vFontSpacing[c - 32].y), 8.0f}, scale, col);
				spos.x += static_cast<float>(vFontSpacing[c - 32].y) * scale.x;
			}
		}
	}

	vi2d PixelGameEngine::GetTextSize(const std::string& s)
	{
		vi2d size = {0, 1};
		vi2d pos = {0, 1};
		for (auto c : s)
		{
			if (c == '\n')
			{
				pos.y++;
				pos.x = 0;
			}
			else pos.x++;
			size.x = std::max(size.x, pos.x);
			size.y = std::max(size.y, pos.y);
		}
		return size * 8;
	}

	void PixelGameEngine::DrawString(const vi2d& pos, const std::string& sText, Pixel col, uint32_t scale)
	{
		DrawString(pos.x, pos.y, sText, col, scale);
	}

	void PixelGameEngine::DrawString(int32_t x, int32_t y, const std::string& sText, Pixel col, uint32_t scale)
	{
		int32_t sx = 0;
		int32_t sy = 0;
		Pixel::Mode m = nPixelMode;
		// Thanks @tucna, spotted bug with col.ALPHA :P
		if (col.a != 255) SetPixelMode(Pixel::ALPHA);
		else SetPixelMode(Pixel::MASK);
		for (auto c : sText)
		{
			if (c == '\n')
			{
				sx = 0;
				sy += 8 * scale;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;

				if (scale > 1)
				{
					for (uint32_t i = 0; i < 8; i++)
						for (uint32_t j = 0; j < 8; j++)
							if (fontSprite->GetPixel(i + ox * 8, j + oy * 8).r > 0)
								for (uint32_t is = 0; is < scale; is++)
									for (uint32_t js = 0; js < scale; js++)
										Draw(x + sx + (i * scale) + is, y + sy + (j * scale) + js, col);
				}
				else
				{
					for (uint32_t i = 0; i < 8; i++)
						for (uint32_t j = 0; j < 8; j++)
							if (fontSprite->GetPixel(i + ox * 8, j + oy * 8).r > 0)
								Draw(x + sx + i, y + sy + j, col);
				}
				sx += 8 * scale;
			}
		}
		SetPixelMode(m);
	}

	vi2d PixelGameEngine::GetTextSizeProp(const std::string& s)
	{
		vi2d size = {0, 1};
		vi2d pos = {0, 1};
		for (auto c : s)
		{
			if (c == '\n')
			{
				pos.y += 8;
				pos.x = 0;
			}
			else pos.x += vFontSpacing[c - 32].y;
			size.x = std::max(size.x, pos.x);
			size.y = std::max(size.y, pos.y);
		}

		size.y *= 8;
		return size;
	}

	void PixelGameEngine::DrawStringProp(const vi2d& pos, const std::string& sText, Pixel col, uint32_t scale)
	{
		DrawStringProp(pos.x, pos.y, sText, col, scale);
	}

	void PixelGameEngine::DrawStringProp(int32_t x, int32_t y, const std::string& sText, Pixel col, uint32_t scale)
	{
		int32_t sx = 0;
		int32_t sy = 0;
		Pixel::Mode m = nPixelMode;

		if (col.a != 255) SetPixelMode(Pixel::ALPHA);
		else SetPixelMode(Pixel::MASK);
		for (auto c : sText)
		{
			if (c == '\n')
			{
				sx = 0;
				sy += 8 * scale;
			}
			else
			{
				int32_t ox = (c - 32) % 16;
				int32_t oy = (c - 32) / 16;

				if (scale > 1)
				{
					for (int32_t i = 0; i < vFontSpacing[c - 32].y; i++)
						for (int32_t j = 0; j < 8; j++)
							if (fontSprite->GetPixel(i + ox * 8 + vFontSpacing[c - 32].x, j + oy * 8).r > 0)
								for (int32_t is = 0; is < static_cast<int>(scale); is++)
									for (int32_t js = 0; js < static_cast<int>(scale); js++)
										Draw(x + sx + (i * scale) + is, y + sy + (j * scale) + js, col);
				}
				else
				{
					for (int32_t i = 0; i < vFontSpacing[c - 32].y; i++)
						for (int32_t j = 0; j < 8; j++)
							if (fontSprite->GetPixel(i + ox * 8 + vFontSpacing[c - 32].x, j + oy * 8).r > 0)
								Draw(x + sx + i, y + sy + j, col);
				}
				sx += vFontSpacing[c - 32].y * scale;
			}
		}
		SetPixelMode(m);
	}

	void PixelGameEngine::SetPixelMode(Pixel::Mode m)
	{
		nPixelMode = m;
	}

	Pixel::Mode PixelGameEngine::GetPixelMode()
	{
		return nPixelMode;
	}

	void PixelGameEngine::SetPixelMode(std::function<Pixel(int x, int y, const Pixel&, const Pixel&)> pixelMode)
	{
		funcPixelMode = pixelMode;
		nPixelMode = Pixel::Mode::CUSTOM;
	}

	void PixelGameEngine::SetPixelBlend(float fBlend)
	{
		fBlendFactor = fBlend;
		if (fBlendFactor < 0.0f) fBlendFactor = 0.0f;
		if (fBlendFactor > 1.0f) fBlendFactor = 1.0f;
	}

	// User must override these functions as required. I have not made
	// them abstract because I do need a default behaviour to occur if
	// they are not overwritten

	bool PixelGameEngine::OnUserCreate()
	{
		return false;
	}

	bool PixelGameEngine::OnUserUpdate(float fElapsedTime)
	{
		UNUSED(fElapsedTime);
		return false;
	}

	bool PixelGameEngine::OnUserDestroy()
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////

	void PixelGameEngine::olc_UpdateViewport()
	{
		int32_t ww = vScreenSize.x * vPixelSize.x;
		int32_t wh = vScreenSize.y * vPixelSize.y;
		float wasp = static_cast<float>(ww) / static_cast<float>(wh);

		if (bPixelCohesion)
		{
			vScreenPixelSize = (vWindowSize / vScreenSize);
			vViewSize = (vWindowSize / vScreenSize) * vScreenSize;
		}
		else
		{
			vViewSize.x = static_cast<int32_t>(vWindowSize.x);
			vViewSize.y = static_cast<int32_t>(static_cast<float>(vViewSize.x) / wasp);

			if (vViewSize.y > vWindowSize.y)
			{
				vViewSize.y = vWindowSize.y;
				vViewSize.x = static_cast<int32_t>(static_cast<float>(vViewSize.y) * wasp);
			}
		}

		vViewPos = (vWindowSize - vViewSize) / 2;
	}

	void PixelGameEngine::olc_UpdateWindowSize(int32_t x, int32_t y)
	{
		vWindowSize = {x, y};
		olc_UpdateViewport();
	}

	void PixelGameEngine::olc_UpdateMouseWheel(int32_t delta)
	{
		nMouseWheelDeltaCache += delta;
	}

	void PixelGameEngine::olc_UpdateMouse(int32_t x, int32_t y)
	{
		// Mouse coords come in screen space
		// But leave in pixel space
		bHasMouseFocus = true;
		vMouseWindowPos = {x, y};
		// Full Screen mode may have a weird viewport we must clamp to
		x -= vViewPos.x;
		y -= vViewPos.y;
		vMousePosCache.x = static_cast<int32_t>((static_cast<float>(x) / static_cast<float>(vWindowSize.x - (vViewPos.x * 2)
		) * static_cast<float>(
			vScreenSize.x)));
		vMousePosCache.y = static_cast<int32_t>((static_cast<float>(y) / static_cast<float>(vWindowSize.y - (vViewPos.y * 2)
		) * static_cast<float>(
			vScreenSize.y)));
		if (vMousePosCache.x >= static_cast<int32_t>(vScreenSize.x)) vMousePosCache.x = vScreenSize.x - 1;
		if (vMousePosCache.y >= static_cast<int32_t>(vScreenSize.y)) vMousePosCache.y = vScreenSize.y - 1;
		if (vMousePosCache.x < 0) vMousePosCache.x = 0;
		if (vMousePosCache.y < 0) vMousePosCache.y = 0;
	}

	void PixelGameEngine::olc_UpdateMouseState(int32_t button, bool state)
	{
		pMouseNewState[button] = state;
	}

	void PixelGameEngine::olc_UpdateKeyState(int32_t key, bool state)
	{
		pKeyNewState[key] = state;
	}

	void PixelGameEngine::olc_UpdateMouseFocus(bool state)
	{
		bHasMouseFocus = state;
	}

	void PixelGameEngine::olc_UpdateKeyFocus(bool state)
	{
		bHasInputFocus = state;
	}

	void PixelGameEngine::olc_Terminate()
	{
		bAtomActive = false;
	}

	void PixelGameEngine::EngineThread()
	{
		// Allow platform to do stuff here if needed, since its now in the
		// context of this thread
		if (platform->ThreadStartUp() == FAIL) return;

		// Do engine context specific initialisation
		olc_PrepareEngine();

		// Create user resources as part of this thread
		if (!OnUserCreate()) bAtomActive = false;

		while (bAtomActive)
		{
			// Run as fast as possible
			while (bAtomActive) { olc_CoreUpdate(); }

			// Allow the user to free resources if they have overrided the destroy function
			if (!OnUserDestroy())
			{
				// User denied destroy for some reason, so continue running
				bAtomActive = true;
			}
		}

		platform->ThreadCleanUp();
	}

	void PixelGameEngine::olc_PrepareEngine()
	{
		// Start OpenGL, the context is owned by the game thread
		if (platform->CreateGraphics(bFullScreen, bEnableVSYNC, vViewPos, vViewSize) == FAIL) return;

		// Construct default font sheet
		olc_ConstructFontSheet();

		// Create Primary Layer "0"
		CreateLayer();
		vLayers[0].bUpdate = true;
		vLayers[0].bShow = true;
		SetDrawTarget(nullptr);

		m_tp1 = std::chrono::system_clock::now();
		m_tp2 = std::chrono::system_clock::now();
	}

	void PixelGameEngine::olc_CoreUpdate()
	{
		// Handle Timing
		m_tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = m_tp2 - m_tp1;
		m_tp1 = m_tp2;

		// Our time per frame coefficient
		float fElapsedTime = elapsedTime.count();
		fLastElapsed = fElapsedTime;

		// Some platforms will need to check for events
		platform->HandleSystemEvent();

		// Compare hardware input states from previous frame
		auto ScanHardware = [&](HWButton* pKeys, bool* pStateOld, bool* pStateNew, uint32_t nKeyCount)
		{
			for (uint32_t i = 0; i < nKeyCount; i++)
			{
				pKeys[i].bPressed = false;
				pKeys[i].bReleased = false;
				if (pStateNew[i] != pStateOld[i])
				{
					if (pStateNew[i])
					{
						pKeys[i].bPressed = !pKeys[i].bHeld;
						pKeys[i].bHeld = true;
					}
					else
					{
						pKeys[i].bReleased = true;
						pKeys[i].bHeld = false;
					}
				}
				pStateOld[i] = pStateNew[i];
			}
		};

		ScanHardware(pKeyboardState, pKeyOldState, pKeyNewState, 256);
		ScanHardware(pMouseState, pMouseOldState, pMouseNewState, nMouseButtons);

		// Cache mouse coordinates so they remain consistent during frame
		vMousePos = vMousePosCache;
		nMouseWheelDelta = nMouseWheelDeltaCache;
		nMouseWheelDeltaCache = 0;

		//	renderer->ClearBuffer(olc::BLACK, true);

		// Handle Frame Update
		if (!OnUserUpdate(fElapsedTime))
			bAtomActive = false;

		// Display Frame
		renderer->UpdateViewport(vViewPos, vViewSize);
		renderer->ClearBuffer(BLACK, true);

		// Layer 0 must always exist
		vLayers[0].bUpdate = true;
		vLayers[0].bShow = true;
		renderer->PrepareDrawing();

		for (auto layer = vLayers.rbegin(); layer != vLayers.rend(); ++layer)
		{
			if (layer->bShow)
			{
				if (layer->funcHook == nullptr)
				{
					renderer->ApplyTexture(layer->nResID);
					if (layer->bUpdate)
					{
						renderer->UpdateTexture(layer->nResID, layer->pDrawTarget);
						layer->bUpdate = false;
					}

					renderer->DrawLayerQuad(layer->vOffset, layer->vScale, layer->tint);

					// Display Decals in order for this layer
					for (auto& decal : layer->vecDecalInstance)
						renderer->DrawDecalQuad(decal);
					layer->vecDecalInstance.clear();
				}
				else
				{
					// Mwa ha ha.... Have Fun!!!
					layer->funcHook();
				}
			}
		}

		// Present Graphics to screen
		renderer->DisplayFrame();

		// Update Title Bar
		fFrameTimer += fElapsedTime;
		nFrameCount++;
		if (fFrameTimer >= 1.0f)
		{
			nLastFPS = nFrameCount;
			fFrameTimer -= 1.0f;
			std::string sTitle = "OneLoneCoder.com - Pixel Game Engine - " + sAppName + " - FPS: " +
				std::to_string(nFrameCount);
			platform->SetWindowTitle(sTitle);
			nFrameCount = 0;
		}
	}

	void PixelGameEngine::olc_ConstructFontSheet()
	{
		std::string data;
		data += "?Q`0001oOch0o01o@F40o0<AGD4090LAGD<090@A7ch0?00O7Q`0600>00000000";
		data += "O000000nOT0063Qo4d8>?7a14Gno94AA4gno94AaOT0>o3`oO400o7QN00000400";
		data += "Of80001oOg<7O7moBGT7O7lABET024@aBEd714AiOdl717a_=TH013Q>00000000";
		data += "720D000V?V5oB3Q_HdUoE7a9@DdDE4A9@DmoE4A;Hg]oM4Aj8S4D84@`00000000";
		data += "OaPT1000Oa`^13P1@AI[?g`1@A=[OdAoHgljA4Ao?WlBA7l1710007l100000000";
		data += "ObM6000oOfMV?3QoBDD`O7a0BDDH@5A0BDD<@5A0BGeVO5ao@CQR?5Po00000000";
		data += "Oc``000?Ogij70PO2D]??0Ph2DUM@7i`2DTg@7lh2GUj?0TO0C1870T?00000000";
		data += "70<4001o?P<7?1QoHg43O;`h@GT0@:@LB@d0>:@hN@L0@?aoN@<0O7ao0000?000";
		data += "OcH0001SOglLA7mg24TnK7ln24US>0PL24U140PnOgl0>7QgOcH0K71S0000A000";
		data += "00H00000@Dm1S007@DUSg00?OdTnH7YhOfTL<7Yh@Cl0700?@Ah0300700000000";
		data += "<008001QL00ZA41a@6HnI<1i@FHLM81M@@0LG81?O`0nC?Y7?`0ZA7Y300080000";
		data += "O`082000Oh0827mo6>Hn?Wmo?6HnMb11MP08@C11H`08@FP0@@0004@000000000";
		data += "00P00001Oab00003OcKP0006@6=PMgl<@440MglH@000000`@000001P00000000";
		data += "Ob@8@@00Ob@8@Ga13R@8Mga172@8?PAo3R@827QoOb@820@0O`0007`0000007P0";
		data += "O`000P08Od400g`<3V=P0G`673IP0`@3>1`00P@6O`P00g`<O`000GP800000000";
		data += "?P9PL020O`<`N3R0@E4HC7b0@ET<ATB0@@l6C4B0O`H3N7b0?P01L3R000000020";

		fontSprite = new Sprite(128, 48);
		int px = 0, py = 0;
		for (size_t b = 0; b < 1024; b += 4)
		{
			uint32_t sym1 = static_cast<uint32_t>(data[b + 0]) - 48;
			uint32_t sym2 = static_cast<uint32_t>(data[b + 1]) - 48;
			uint32_t sym3 = static_cast<uint32_t>(data[b + 2]) - 48;
			uint32_t sym4 = static_cast<uint32_t>(data[b + 3]) - 48;
			uint32_t r = sym1 << 18 | sym2 << 12 | sym3 << 6 | sym4;

			for (int i = 0; i < 24; i++)
			{
				int k = r & (1 << i) ? 255 : 0;
				fontSprite->SetPixel(px, py, Pixel(k, k, k, k));
				if (++py == 48)
				{
					px++;
					py = 0;
				}
			}
		}

		fontDecal = new Decal(fontSprite);

		constexpr std::array<uint8_t, 96> vSpacing = {
			{
				0x03, 0x25, 0x16, 0x08, 0x07, 0x08, 0x08, 0x04, 0x15, 0x15, 0x08, 0x07, 0x15, 0x07, 0x24, 0x08,
				0x08, 0x17, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x24, 0x15, 0x06, 0x07, 0x16, 0x17,
				0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x17, 0x08, 0x08, 0x17, 0x08, 0x08, 0x08,
				0x08, 0x08, 0x08, 0x08, 0x17, 0x08, 0x08, 0x08, 0x08, 0x17, 0x08, 0x15, 0x08, 0x15, 0x08, 0x08,
				0x24, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x33, 0x17, 0x17, 0x33, 0x18, 0x17, 0x17,
				0x17, 0x17, 0x17, 0x17, 0x07, 0x17, 0x17, 0x18, 0x18, 0x17, 0x17, 0x07, 0x33, 0x07, 0x08, 0x00,
			}
		};

		for (auto c : vSpacing) vFontSpacing.push_back({c >> 4, c & 15});
	}

	// Need a couple of statics as these are singleton instances
	// read from multiple locations
	std::atomic<bool> PixelGameEngine::bAtomActive{false};
	PixelGameEngine* PGEX::pge = nullptr;
	PixelGameEngine* Platform::ptrPGE = nullptr;
	PixelGameEngine* Renderer::ptrPGE = nullptr;
	std::unique_ptr<ImageLoader> Sprite::loader = nullptr;
};

// O------------------------------------------------------------------------------O
// | olcPixelGameEngine PLATFORM SPECIFIC IMPLEMENTATIONS                         |
// O------------------------------------------------------------------------------O

// O------------------------------------------------------------------------------O
// | START RENDERER: OpenGL 1.0 (the original, the best...)                       |
// O------------------------------------------------------------------------------O
#if defined(OLC_GFX_OPENGL10)
#if defined(OLC_PLATFORM_WINAPI)
#include <dwmapi.h>
#include <GL/gl.h>

#if !defined(__MINGW32__)
#pragma comment(lib, "Dwmapi.lib")
#endif
typedef BOOL (WINAPI wglSwapInterval_t)(int interval);
static wglSwapInterval_t* wglSwapInterval = nullptr;
typedef HDC glDeviceContext_t;
typedef HGLRC glRenderContext_t;
#endif

#if defined(__linux__) || defined(__FreeBSD__)
#include <GL/gl.h>
#endif

#if defined(OLC_PLATFORM_X11)
namespace X11
{
#include <GL/glx.h>
}

typedef int(glSwapInterval_t)(X11::Display* dpy, X11::GLXDrawable drawable, int interval);
static glSwapInterval_t* glSwapIntervalEXT;
typedef X11::GLXContext glDeviceContext_t;
typedef X11::GLXContext glRenderContext_t;
#endif

#if defined(__APPLE__)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

namespace olc
{
	class Renderer_OGL10 : public Renderer
	{
	private:
#if defined(OLC_PLATFORM_GLUT)
		bool mFullScreen = false;
#else
		glDeviceContext_t glDeviceContext = nullptr;
		glRenderContext_t glRenderContext = nullptr;
#endif

		bool bSync = false;
		DecalMode nDecalMode = static_cast<DecalMode>(-1); // Thanks Gusgo & Bispoo

#if defined(OLC_PLATFORM_X11)
		X11::Display* olc_Display = nullptr;
		X11::Window* olc_Window = nullptr;
		X11::XVisualInfo* olc_VisualInfo = nullptr;
#endif

	public:
		void PrepareDevice() override
		{
#if defined(OLC_PLATFORM_GLUT)
			//glutInit has to be called with main() arguments, make fake ones
			int argc = 0;
			char* argv[1] = { (char*)"" };
			glutInit(&argc, argv);

			glutInitWindowPosition(0, 0);
			glutInitWindowSize(512, 512);

			glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

			// Creates the window and the OpenGL context for it
			glutCreateWindow("OneLoneCoder.com - Pixel Game Engine");

			glEnable(GL_TEXTURE_2D); // Turn on texturing
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
#endif
		}

		rcode CreateDevice(std::vector<void*> params, bool bFullScreen, bool bVSYNC) override
		{
#if defined(OLC_PLATFORM_WINAPI)
			// Create Device Context
			glDeviceContext = GetDC(static_cast<HWND>(params[0]));
			PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR), 1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				PFD_MAIN_PLANE, 0, 0, 0, 0
			};

			int pf = 0;
			if (!(pf = ChoosePixelFormat(glDeviceContext, &pfd))) return FAIL;
			SetPixelFormat(glDeviceContext, pf, &pfd);

			if (!(glRenderContext = wglCreateContext(glDeviceContext))) return FAIL;
			wglMakeCurrent(glDeviceContext, glRenderContext);

			// Remove Frame cap
			wglSwapInterval = (wglSwapInterval_t*)wglGetProcAddress("wglSwapIntervalEXT");
			if (wglSwapInterval && !bVSYNC) wglSwapInterval(0);
			bSync = bVSYNC;
#endif

#if defined(OLC_PLATFORM_X11)
			using namespace X11;
			// Linux has tighter coupling between OpenGL and X11, so we store
			// various "platform" handles in the renderer
			olc_Display = (X11::Display*)(params[0]);
			olc_Window = (X11::Window*)(params[1]);
			olc_VisualInfo = (X11::XVisualInfo*)(params[2]);

			glDeviceContext = glXCreateContext(olc_Display, olc_VisualInfo, nullptr, GL_TRUE);
			glXMakeCurrent(olc_Display, *olc_Window, glDeviceContext);

			XWindowAttributes gwa;
			XGetWindowAttributes(olc_Display, *olc_Window, &gwa);
			glViewport(0, 0, gwa.width, gwa.height);

			glSwapIntervalEXT = nullptr;
			glSwapIntervalEXT = (glSwapInterval_t*)glXGetProcAddress((unsigned char*)"glXSwapIntervalEXT");

			if (glSwapIntervalEXT == nullptr && !bVSYNC)
			{
				printf("NOTE: Could not disable VSYNC, glXSwapIntervalEXT() was not found!\n");
				printf("      Don't worry though, things will still work, it's just the\n");
				printf("      frame rate will be capped to your monitors refresh rate - javidx9\n");
			}

			if (glSwapIntervalEXT != nullptr && !bVSYNC)
				glSwapIntervalEXT(olc_Display, *olc_Window, 0);
#endif

#if defined(OLC_PLATFORM_GLUT)
			mFullScreen = bFullScreen;
			if (!bVSYNC)
			{
#if defined(__APPLE__)
				GLint sync = 0;
				CGLContextObj ctx = CGLGetCurrentContext();
				if (ctx) CGLSetParameter(ctx, kCGLCPSwapInterval, &sync);
#endif
			}
#else
			glEnable(GL_TEXTURE_2D); // Turn on texturing
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
#endif
			return OK;
		}

		rcode DestroyDevice() override
		{
#if defined(OLC_PLATFORM_WINAPI)
			wglDeleteContext(glRenderContext);
#endif

#if defined(OLC_PLATFORM_X11)
			glXMakeCurrent(olc_Display, None, NULL);
			glXDestroyContext(olc_Display, glDeviceContext);
#endif

#if defined(OLC_PLATFORM_GLUT)
			glutDestroyWindow(glutGetWindow());
#endif
			return OK;
		}

		void DisplayFrame() override
		{
#if defined(OLC_PLATFORM_WINAPI)
			SwapBuffers(glDeviceContext);
			if (bSync) DwmFlush(); // Woooohooooooo!!!! SMOOOOOOOTH!
#endif

#if defined(OLC_PLATFORM_X11)
			X11::glXSwapBuffers(olc_Display, *olc_Window);
#endif

#if defined(OLC_PLATFORM_GLUT)
			glutSwapBuffers();
#endif
		}

		void PrepareDrawing() override
		{
			glEnable(GL_BLEND);
			SetDecalMode(DecalMode::NORMAL);
		}

		void SetDecalMode(const DecalMode& mode) override
		{
			if (mode != nDecalMode)
			{
				switch (mode)
				{
				case DecalMode::NORMAL:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					break;
				case DecalMode::ADDITIVE:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE);
					break;
				case DecalMode::MULTIPLICATIVE:
					glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
					break;
				case DecalMode::STENCIL:
					glBlendFunc(GL_ZERO, GL_SRC_ALPHA);
					break;
				case DecalMode::ILLUMINATE:
					glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
					break;
				}

				nDecalMode = mode;
			}
		}

		void DrawLayerQuad(const vf2d& offset, const vf2d& scale, const Pixel tint) override
		{
			glBegin(GL_QUADS);
			glColor4ub(tint.r, tint.g, tint.b, tint.a);
			glTexCoord2f(0.0f * scale.x + offset.x, 1.0f * scale.y + offset.y);
			glVertex3f(-1.0f /*+ vSubPixelOffset.x*/, -1.0f /*+ vSubPixelOffset.y*/, 0.0f);
			glTexCoord2f(0.0f * scale.x + offset.x, 0.0f * scale.y + offset.y);
			glVertex3f(-1.0f /*+ vSubPixelOffset.x*/, 1.0f /*+ vSubPixelOffset.y*/, 0.0f);
			glTexCoord2f(1.0f * scale.x + offset.x, 0.0f * scale.y + offset.y);
			glVertex3f(1.0f /*+ vSubPixelOffset.x*/, 1.0f /*+ vSubPixelOffset.y*/, 0.0f);
			glTexCoord2f(1.0f * scale.x + offset.x, 1.0f * scale.y + offset.y);
			glVertex3f(1.0f /*+ vSubPixelOffset.x*/, -1.0f /*+ vSubPixelOffset.y*/, 0.0f);
			glEnd();
		}

		void DrawDecalQuad(const DecalInstance& decal) override
		{
			if (decal.decal == nullptr)
			{
				SetDecalMode(decal.mode);
				glBindTexture(GL_TEXTURE_2D, 0);
				glBegin(GL_QUADS);
				glColor4ub(decal.tint[0].r, decal.tint[0].g, decal.tint[0].b, decal.tint[0].a);
				glTexCoord4f(decal.uv[0].x, decal.uv[0].y, 0.0f, decal.w[0]);
				glVertex2f(decal.pos[0].x, decal.pos[0].y);
				glColor4ub(decal.tint[1].r, decal.tint[1].g, decal.tint[1].b, decal.tint[1].a);
				glTexCoord4f(decal.uv[1].x, decal.uv[1].y, 0.0f, decal.w[1]);
				glVertex2f(decal.pos[1].x, decal.pos[1].y);
				glColor4ub(decal.tint[2].r, decal.tint[2].g, decal.tint[2].b, decal.tint[2].a);
				glTexCoord4f(decal.uv[2].x, decal.uv[2].y, 0.0f, decal.w[2]);
				glVertex2f(decal.pos[2].x, decal.pos[2].y);
				glColor4ub(decal.tint[3].r, decal.tint[3].g, decal.tint[3].b, decal.tint[3].a);
				glTexCoord4f(decal.uv[3].x, decal.uv[3].y, 0.0f, decal.w[3]);
				glVertex2f(decal.pos[3].x, decal.pos[3].y);
				glEnd();
			}
			else
			{
				SetDecalMode(decal.mode);
				glBindTexture(GL_TEXTURE_2D, decal.decal->id);
				glBegin(GL_QUADS);
				glColor4ub(decal.tint[0].r, decal.tint[0].g, decal.tint[0].b, decal.tint[0].a);
				glTexCoord4f(decal.uv[0].x, decal.uv[0].y, 0.0f, decal.w[0]);
				glVertex2f(decal.pos[0].x, decal.pos[0].y);
				glTexCoord4f(decal.uv[1].x, decal.uv[1].y, 0.0f, decal.w[1]);
				glVertex2f(decal.pos[1].x, decal.pos[1].y);
				glTexCoord4f(decal.uv[2].x, decal.uv[2].y, 0.0f, decal.w[2]);
				glVertex2f(decal.pos[2].x, decal.pos[2].y);
				glTexCoord4f(decal.uv[3].x, decal.uv[3].y, 0.0f, decal.w[3]);
				glVertex2f(decal.pos[3].x, decal.pos[3].y);
				glEnd();
			}
		}

		uint32_t CreateTexture(const uint32_t width, const uint32_t height, const bool filtered) override
		{
			UNUSED(width);
			UNUSED(height);
			uint32_t id = 0;
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			if (filtered)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			return id;
		}

		uint32_t DeleteTexture(const uint32_t id) override
		{
			glDeleteTextures(1, &id);
			return id;
		}

		void UpdateTexture(uint32_t id, Sprite* spr) override
		{
			UNUSED(id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spr->width, spr->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, spr->GetData());
		}

		void ApplyTexture(uint32_t id) override
		{
			glBindTexture(GL_TEXTURE_2D, id);
		}

		void ClearBuffer(Pixel p, bool bDepth) override
		{
			glClearColor(static_cast<float>(p.r) / 255.0f, static_cast<float>(p.g) / 255.0f, static_cast<float>(p.b) / 255.0f,
			             static_cast<float>(p.a) / 255.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			if (bDepth) glClear(GL_DEPTH_BUFFER_BIT);
		}

		void UpdateViewport(const vi2d& pos, const vi2d& size) override
		{
#if defined(OLC_PLATFORM_GLUT)
			if (!mFullScreen) glutReshapeWindow(size.x, size.y);
#else
			glViewport(pos.x, pos.y, size.x, size.y);
#endif
		}
	};
}
#endif
// O------------------------------------------------------------------------------O
// | END RENDERER: OpenGL 1.0 (the original, the best...)                         |
// O------------------------------------------------------------------------------O

// O------------------------------------------------------------------------------O
// | START IMAGE LOADER: GDI+, Windows Only, always exists, a little slow         |
// O------------------------------------------------------------------------------O
#if defined(OLC_IMAGE_GDI)

#define min(a, b) ((a < b) ? a : b)
#define max(a, b) ((a > b) ? a : b)
#include <gdiplus.h>
#include <shlwapi.h>
#undef min
#undef max

#if !defined(__MINGW32__)
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "Shlwapi.lib")
#endif

namespace olc
{
	// Thanks @MaGetzUb for this, which allows sprites to be defined
	// at construction, by initialising the GDI subsystem
	static class GDIPlusStartup
	{
	public:
		GDIPlusStartup()
		{
			Gdiplus::GdiplusStartupInput startupInput;
			ULONG_PTR token;
			GdiplusStartup(&token, &startupInput, nullptr);
		};
	} gdistartup;

	class ImageLoader_GDIPlus : public ImageLoader
	{
	private:
		std::wstring ConvertS2W(std::string s)
		{
#ifdef __MINGW32__
			wchar_t* buffer = new wchar_t[s.length() + 1];
			mbstowcs(buffer, s.c_str(), s.length());
			buffer[s.length()] = L'\0';
#else
			int count = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
			wchar_t* buffer = new wchar_t[count];
			MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, buffer, count);
#endif
			std::wstring w(buffer);
			delete[] buffer;
			return w;
		}

	public:
		ImageLoader_GDIPlus() : ImageLoader()
		{
		}

		rcode LoadImageResource(Sprite* spr, const std::string& sImageFile, ResourcePack* pack) override
		{
			// clear out existing sprite
			if (spr->pColData != nullptr) delete[] spr->pColData;

			// Open file
			UNUSED(pack);
			Gdiplus::Bitmap* bmp = nullptr;
			if (pack != nullptr)
			{
				// Load sprite from input stream
				ResourceBuffer rb = pack->GetFileBuffer(sImageFile);
				bmp = Gdiplus::Bitmap::FromStream(
					SHCreateMemStream((BYTE*)rb.vMemory.data(), static_cast<UINT>(rb.vMemory.size())));
			}
			else
			{
				// Check file exists
				if (!_gfs::exists(sImageFile)) return NO_FILE;

				// Load sprite from file
				bmp = Gdiplus::Bitmap::FromFile(ConvertS2W(sImageFile).c_str());
			}

			if (bmp->GetLastStatus() != Gdiplus::Ok) return FAIL;
			spr->width = bmp->GetWidth();
			spr->height = bmp->GetHeight();
			spr->pColData = new Pixel[spr->width * spr->height];

			for (int y = 0; y < spr->height; y++)
				for (int x = 0; x < spr->width; x++)
				{
					Gdiplus::Color c;
					bmp->GetPixel(x, y, &c);
					spr->SetPixel(x, y, Pixel(c.GetRed(), c.GetGreen(), c.GetBlue(), c.GetAlpha()));
				}
			delete bmp;
			return OK;
		}

		rcode SaveImageResource(Sprite* spr, const std::string& sImageFile) override
		{
			return OK;
		}
	};
}
#endif
// O------------------------------------------------------------------------------O
// | END IMAGE LOADER: GDI+                                                       |
// O------------------------------------------------------------------------------O

// O------------------------------------------------------------------------------O
// | START IMAGE LOADER: libpng, default on linux, requires -lpng  (libpng-dev)   |
// O------------------------------------------------------------------------------O
#if defined(OLC_IMAGE_LIBPNG)
#include <png.h>
namespace olc
{
	void pngReadStream(png_structp pngPtr, png_bytep data, png_size_t length)
	{
		png_voidp a = png_get_io_ptr(pngPtr);
		((std::istream*)a)->read((char*)data, length);
	}

	class ImageLoader_LibPNG : public olc::ImageLoader
	{
	public:
		ImageLoader_LibPNG() : ImageLoader()
		{}

		olc::rcode LoadImageResource(olc::Sprite* spr, const std::string& sImageFile, olc::ResourcePack* pack) override
		{
			UNUSED(pack);

			// clear out existing sprite
			if (spr->pColData != nullptr) delete[] spr->pColData;

			////////////////////////////////////////////////////////////////////////////
			// Use libpng, Thanks to Guillaume Cottenceau
			// https://gist.github.com/niw/5963798
			// Also reading png from streams
			// http://www.piko3d.net/tutorials/libpng-tutorial-loading-png-files-from-streams/
			png_structp png;
			png_infop info;

			auto loadPNG = [&]()
			{
				png_read_info(png, info);
				png_byte color_type;
				png_byte bit_depth;
				png_bytep* row_pointers;
				spr->width = png_get_image_width(png, info);
				spr->height = png_get_image_height(png, info);
				color_type = png_get_color_type(png, info);
				bit_depth = png_get_bit_depth(png, info);
				if (bit_depth == 16) png_set_strip_16(png);
				if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);
				if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)	png_set_expand_gray_1_2_4_to_8(png);
				if (png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);
				if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
					png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
				if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
					png_set_gray_to_rgb(png);
				png_read_update_info(png, info);
				row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * spr->height);
				for (int y = 0; y < spr->height; y++) {
					row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png, info));
				}
				png_read_image(png, row_pointers);
				////////////////////////////////////////////////////////////////////////////
				// Create sprite array
				spr->pColData = new Pixel[spr->width * spr->height];
				// Iterate through image rows, converting into sprite format
				for (int y = 0; y < spr->height; y++)
				{
					png_bytep row = row_pointers[y];
					for (int x = 0; x < spr->width; x++)
					{
						png_bytep px = &(row[x * 4]);
						spr->SetPixel(x, y, Pixel(px[0], px[1], px[2], px[3]));
					}
				}

				for (int y = 0; y < spr->height; y++) // Thanks maksym33
					free(row_pointers[y]);
				free(row_pointers);
				png_destroy_read_struct(&png, &info, nullptr);
			};

			png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			if (!png) goto fail_load;

			info = png_create_info_struct(png);
			if (!info) goto fail_load;

			if (setjmp(png_jmpbuf(png))) goto fail_load;

			if (pack == nullptr)
			{
				FILE* f = fopen(sImageFile.c_str(), "rb");
				if (!f) return olc::rcode::NO_FILE;
				png_init_io(png, f);
				loadPNG();
				fclose(f);
			}
			else
			{
				ResourceBuffer rb = pack->GetFileBuffer(sImageFile);
				std::istream is(&rb);
				png_set_read_fn(png, (png_voidp)&is, pngReadStream);
				loadPNG();
			}

			return olc::rcode::OK;

		fail_load:
			spr->width = 0;
			spr->height = 0;
			spr->pColData = nullptr;
			return olc::rcode::FAIL;
		}

		olc::rcode SaveImageResource(olc::Sprite* spr, const std::string& sImageFile) override
		{
			return olc::rcode::OK;
		}
	};
}
#endif
// O------------------------------------------------------------------------------O
// | END IMAGE LOADER:                                                            |
// O------------------------------------------------------------------------------O

// O------------------------------------------------------------------------------O
// | START IMAGE LOADER: stb_image.h, all systems, very fast                      |
// O------------------------------------------------------------------------------O
// Thanks to Sean Barrett - https://github.com/nothings/stb/blob/master/stb_image.h
// MIT License - Copyright(c) 2017 Sean Barrett

// Note you need to download the above file into your project folder, and
// #define OLC_IMAGE_STB
// #define OLC_PGE_APPLICATION
// #include "olcPixelGameEngine.h"

#if defined(OLC_IMAGE_STB)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
namespace olc
{
	class ImageLoader_STB : public olc::ImageLoader
	{
	public:
		ImageLoader_STB() : ImageLoader()
		{}

		olc::rcode LoadImageResource(olc::Sprite* spr, const std::string& sImageFile, olc::ResourcePack* pack) override
		{
			UNUSED(pack);
			// clear out existing sprite
			if (spr->pColData != nullptr) delete[] spr->pColData;
			// Open file
			stbi_uc* bytes = nullptr;
			int w = 0, h = 0, cmp = 0;
			if (pack != nullptr)
			{
				ResourceBuffer rb = pack->GetFileBuffer(sImageFile);
				bytes = stbi_load_from_memory((unsigned char*)rb.vMemory.data(), rb.vMemory.size(), &w, &h, &cmp, 4);
			}
			else
			{
				// Check file exists
				if (!_gfs::exists(sImageFile)) return olc::rcode::NO_FILE;
				bytes = stbi_load(sImageFile.c_str(), &w, &h, &cmp, 4);
			}

			if (!bytes) return olc::rcode::FAIL;
			spr->width = w; spr->height = h;
			spr->pColData = new Pixel[spr->width * spr->height];
			std::memcpy(spr->pColData, bytes, spr->width * spr->height * 4);
			delete[] bytes;
			return olc::rcode::OK;
		}

		olc::rcode SaveImageResource(olc::Sprite* spr, const std::string& sImageFile) override
		{
			return olc::rcode::OK;
		}
	};
}
#endif
// O------------------------------------------------------------------------------O
// | START IMAGE LOADER: stb_image.h                                              |
// O------------------------------------------------------------------------------O

// O------------------------------------------------------------------------------O
// | START PLATFORM: MICROSOFT WINDOWS XP, VISTA, 7, 8, 10                        |
// O------------------------------------------------------------------------------O
#if defined(OLC_PLATFORM_WINAPI)

#if defined(_WIN32) && !defined(__MINGW32__)
#pragma comment(lib, "user32.lib")		// Visual Studio Only
#pragma comment(lib, "gdi32.lib")		// For other Windows Compilers please add
#pragma comment(lib, "opengl32.lib")	// these libs to your linker input
#endif

namespace olc
{
	class Platform_Windows : public Platform
	{
	private:
		HWND olc_hWnd = nullptr;
		std::wstring wsAppName;

		std::wstring ConvertS2W(std::string s)
		{
#ifdef __MINGW32__
			wchar_t* buffer = new wchar_t[s.length() + 1];
			mbstowcs(buffer, s.c_str(), s.length());
			buffer[s.length()] = L'\0';
#else
			int count = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
			wchar_t* buffer = new wchar_t[count];
			MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, buffer, count);
#endif
			std::wstring w(buffer);
			delete[] buffer;
			return w;
		}

	public:
		rcode ApplicationStartUp() override { return OK; }
		rcode ApplicationCleanUp() override { return OK; }
		rcode ThreadStartUp() override { return OK; }

		rcode ThreadCleanUp() override
		{
			renderer->DestroyDevice();
			PostMessage(olc_hWnd, WM_DESTROY, 0, 0);
			return OK;
		}

		rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const vi2d& vViewPos, const vi2d& vViewSize) override
		{
			if (renderer->CreateDevice({olc_hWnd}, bFullScreen, bEnableVSYNC) == OK)
			{
				renderer->UpdateViewport(vViewPos, vViewSize);
				return OK;
			}
			return FAIL;
		}

		rcode CreateWindowPane(const vi2d& vWindowPos, vi2d& vWindowSize, bool bFullScreen) override
		{
			WNDCLASS wc;
			wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
			wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
			wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wc.hInstance = GetModuleHandle(nullptr);
			wc.lpfnWndProc = olc_WindowEvent;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.lpszMenuName = nullptr;
			wc.hbrBackground = nullptr;
			wc.lpszClassName = olcT("OLC_PIXEL_GAME_ENGINE");
			RegisterClass(&wc);

			// Define window furniture
			DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME;

			vi2d vTopLeft = vWindowPos;

			// Handle Fullscreen
			if (bFullScreen)
			{
				dwExStyle = 0;
				dwStyle = WS_VISIBLE | WS_POPUP;
				HMONITOR hmon = MonitorFromWindow(olc_hWnd, MONITOR_DEFAULTTONEAREST);
				MONITORINFO mi = {sizeof(mi)};
				if (!GetMonitorInfo(hmon, &mi)) return FAIL;
				vWindowSize = {mi.rcMonitor.right, mi.rcMonitor.bottom};
				vTopLeft.x = 0;
				vTopLeft.y = 0;
			}

			// Keep client size as requested
			RECT rWndRect = {0, 0, vWindowSize.x, vWindowSize.y};
			AdjustWindowRectEx(&rWndRect, dwStyle, FALSE, dwExStyle);
			int width = rWndRect.right - rWndRect.left;
			int height = rWndRect.bottom - rWndRect.top;

			olc_hWnd = CreateWindowEx(dwExStyle, olcT("OLC_PIXEL_GAME_ENGINE"), olcT(""), dwStyle,
			                          vTopLeft.x, vTopLeft.y, width, height, nullptr, nullptr, GetModuleHandle(nullptr),
			                          this);

			// Create Keyboard Mapping
			mapKeys[0x00] = NONE;
			mapKeys[0x41] = A;
			mapKeys[0x42] = B;
			mapKeys[0x43] = C;
			mapKeys[0x44] = D;
			mapKeys[0x45] = E;
			mapKeys[0x46] = F;
			mapKeys[0x47] = G;
			mapKeys[0x48] = H;
			mapKeys[0x49] = I;
			mapKeys[0x4A] = J;
			mapKeys[0x4B] = K;
			mapKeys[0x4C] = L;
			mapKeys[0x4D] = M;
			mapKeys[0x4E] = N;
			mapKeys[0x4F] = O;
			mapKeys[0x50] = P;
			mapKeys[0x51] = Q;
			mapKeys[0x52] = R;
			mapKeys[0x53] = S;
			mapKeys[0x54] = T;
			mapKeys[0x55] = U;
			mapKeys[0x56] = V;
			mapKeys[0x57] = W;
			mapKeys[0x58] = X;
			mapKeys[0x59] = Y;
			mapKeys[0x5A] = Z;

			mapKeys[VK_F1] = F1;
			mapKeys[VK_F2] = F2;
			mapKeys[VK_F3] = F3;
			mapKeys[VK_F4] = F4;
			mapKeys[VK_F5] = F5;
			mapKeys[VK_F6] = F6;
			mapKeys[VK_F7] = F7;
			mapKeys[VK_F8] = F8;
			mapKeys[VK_F9] = F9;
			mapKeys[VK_F10] = F10;
			mapKeys[VK_F11] = F11;
			mapKeys[VK_F12] = F12;

			mapKeys[VK_DOWN] = DOWN;
			mapKeys[VK_LEFT] = LEFT;
			mapKeys[VK_RIGHT] = RIGHT;
			mapKeys[VK_UP] = UP;
			mapKeys[VK_RETURN] = ENTER; //mapKeys[VK_RETURN] = Key::RETURN;

			mapKeys[VK_BACK] = BACK;
			mapKeys[VK_ESCAPE] = ESCAPE;
			mapKeys[VK_RETURN] = ENTER;
			mapKeys[VK_PAUSE] = PAUSE;
			mapKeys[VK_SCROLL] = SCROLL;
			mapKeys[VK_TAB] = TAB;
			mapKeys[VK_DELETE] = DEL;
			mapKeys[VK_HOME] = HOME;
			mapKeys[VK_END] = END;
			mapKeys[VK_PRIOR] = PGUP;
			mapKeys[VK_NEXT] = PGDN;
			mapKeys[VK_INSERT] = INS;
			mapKeys[VK_SHIFT] = SHIFT;
			mapKeys[VK_CONTROL] = CTRL;
			mapKeys[VK_SPACE] = SPACE;

			mapKeys[0x30] = K0;
			mapKeys[0x31] = K1;
			mapKeys[0x32] = K2;
			mapKeys[0x33] = K3;
			mapKeys[0x34] = K4;
			mapKeys[0x35] = K5;
			mapKeys[0x36] = K6;
			mapKeys[0x37] = K7;
			mapKeys[0x38] = K8;
			mapKeys[0x39] = K9;

			mapKeys[VK_NUMPAD0] = NP0;
			mapKeys[VK_NUMPAD1] = NP1;
			mapKeys[VK_NUMPAD2] = NP2;
			mapKeys[VK_NUMPAD3] = NP3;
			mapKeys[VK_NUMPAD4] =
				NP4;
			mapKeys[VK_NUMPAD5] = NP5;
			mapKeys[VK_NUMPAD6] = NP6;
			mapKeys[VK_NUMPAD7] = NP7;
			mapKeys[VK_NUMPAD8] = NP8;
			mapKeys[VK_NUMPAD9] =
				NP9;
			mapKeys[VK_MULTIPLY] = NP_MUL;
			mapKeys[VK_ADD] = NP_ADD;
			mapKeys[VK_DIVIDE] = NP_DIV;
			mapKeys[VK_SUBTRACT] =
				NP_SUB;
			mapKeys[VK_DECIMAL] = NP_DECIMAL;

			// Thanks scripticuk
			mapKeys[VK_OEM_1] = OEM_1; // On US and UK keyboards this is the ';:' key
			mapKeys[VK_OEM_2] = OEM_2; // On US and UK keyboards this is the '/?' key
			mapKeys[VK_OEM_3] = OEM_3; // On US keyboard this is the '~' key
			mapKeys[VK_OEM_4] = OEM_4; // On US and UK keyboards this is the '[{' key
			mapKeys[VK_OEM_5] = OEM_5; // On US keyboard this is '\|' key.
			mapKeys[VK_OEM_6] = OEM_6; // On US and UK keyboards this is the ']}' key
			mapKeys[VK_OEM_7] = OEM_7;
			// On US keyboard this is the single/double quote key. On UK, this is the single quote/@ symbol key
			mapKeys[VK_OEM_8] = OEM_8; // miscellaneous characters. Varies by keyboard
			mapKeys[VK_OEM_PLUS] = EQUALS; // the '+' key on any keyboard
			mapKeys[VK_OEM_COMMA] = COMMA; // the comma key on any keyboard
			mapKeys[VK_OEM_MINUS] = MINUS; // the minus key on any keyboard
			mapKeys[VK_OEM_PERIOD] = PERIOD; // the period key on any keyboard
			mapKeys[VK_CAPITAL] = CAPS_LOCK;
			return OK;
		}

		rcode SetWindowTitle(const std::string& s) override
		{
#ifdef UNICODE
			SetWindowText(olc_hWnd, ConvertS2W(s).c_str());
#else
			SetWindowText(olc_hWnd, s.c_str());
#endif
			return OK;
		}

		rcode StartSystemEventLoop() override
		{
			MSG msg;
			while (GetMessage(&msg, nullptr, 0, 0) > 0)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return OK;
		}

		rcode HandleSystemEvent() override { return FAIL; }

		// Windows Event Handler - this is statically connected to the windows event system
		static LRESULT CALLBACK olc_WindowEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			switch (uMsg)
			{
			case WM_MOUSEMOVE:
				{
					// Thanks @ForAbby (Discord)
					uint16_t x = lParam & 0xFFFF;
					uint16_t y = (lParam >> 16) & 0xFFFF;
					int16_t ix = *(int16_t*)&x;
					int16_t iy = *(int16_t*)&y;
					ptrPGE->olc_UpdateMouse(ix, iy);
					return 0;
				}
			case WM_SIZE: ptrPGE->olc_UpdateWindowSize(lParam & 0xFFFF, (lParam >> 16) & 0xFFFF);
				return 0;
			case WM_MOUSEWHEEL: ptrPGE->olc_UpdateMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));
				return 0;
			case WM_MOUSELEAVE: ptrPGE->olc_UpdateMouseFocus(false);
				return 0;
			case WM_SETFOCUS: ptrPGE->olc_UpdateKeyFocus(true);
				return 0;
			case WM_KILLFOCUS: ptrPGE->olc_UpdateKeyFocus(false);
				return 0;
			case WM_KEYDOWN: ptrPGE->olc_UpdateKeyState(mapKeys[wParam], true);
				return 0;
			case WM_KEYUP: ptrPGE->olc_UpdateKeyState(mapKeys[wParam], false);
				return 0;
			case WM_SYSKEYDOWN: ptrPGE->olc_UpdateKeyState(mapKeys[wParam], true);
				return 0;
			case WM_SYSKEYUP: ptrPGE->olc_UpdateKeyState(mapKeys[wParam], false);
				return 0;
			case WM_LBUTTONDOWN: ptrPGE->olc_UpdateMouseState(0, true);
				return 0;
			case WM_LBUTTONUP: ptrPGE->olc_UpdateMouseState(0, false);
				return 0;
			case WM_RBUTTONDOWN: ptrPGE->olc_UpdateMouseState(1, true);
				return 0;
			case WM_RBUTTONUP: ptrPGE->olc_UpdateMouseState(1, false);
				return 0;
			case WM_MBUTTONDOWN: ptrPGE->olc_UpdateMouseState(2, true);
				return 0;
			case WM_MBUTTONUP: ptrPGE->olc_UpdateMouseState(2, false);
				return 0;
			case WM_CLOSE: ptrPGE->olc_Terminate();
				return 0;
			case WM_DESTROY: PostQuitMessage(0);
				DestroyWindow(hWnd);
				return 0;
			}
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	};
}
#endif
// O------------------------------------------------------------------------------O
// | END PLATFORM: MICROSOFT WINDOWS XP, VISTA, 7, 8, 10                          |
// O------------------------------------------------------------------------------O

// O------------------------------------------------------------------------------O
// | START PLATFORM: LINUX                                                        |
// O------------------------------------------------------------------------------O
#if defined(OLC_PLATFORM_X11)
namespace olc
{
	class Platform_Linux : public olc::Platform
	{
	private:
		X11::Display* olc_Display = nullptr;
		X11::Window					 olc_WindowRoot;
		X11::Window					 olc_Window;
		X11::XVisualInfo* olc_VisualInfo;
		X11::Colormap                olc_ColourMap;
		X11::XSetWindowAttributes    olc_SetWindowAttribs;

	public:
		virtual olc::rcode ApplicationStartUp() override
		{
			return olc::rcode::OK;
		}

		virtual olc::rcode ApplicationCleanUp() override
		{
			return olc::rcode::OK;
		}

		virtual olc::rcode ThreadStartUp() override
		{
			return olc::rcode::OK;
		}

		virtual olc::rcode ThreadCleanUp() override
		{
			renderer->DestroyDevice();
			return olc::OK;
		}

		virtual olc::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc::vi2d& vViewPos, const olc::vi2d& vViewSize) override
		{
			if (renderer->CreateDevice({ olc_Display, &olc_Window, olc_VisualInfo }, bFullScreen, bEnableVSYNC) == olc::rcode::OK)
			{
				renderer->UpdateViewport(vViewPos, vViewSize);
				return olc::rcode::OK;
			}
			else
				return olc::rcode::FAIL;
		}

		virtual olc::rcode CreateWindowPane(const olc::vi2d& vWindowPos, olc::vi2d& vWindowSize, bool bFullScreen) override
		{
			using namespace X11;
			XInitThreads();

			// Grab the deafult display and window
			olc_Display = XOpenDisplay(NULL);
			olc_WindowRoot = DefaultRootWindow(olc_Display);

			// Based on the display capabilities, configure the appearance of the window
			GLint olc_GLAttribs[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
			olc_VisualInfo = glXChooseVisual(olc_Display, 0, olc_GLAttribs);
			olc_ColourMap = XCreateColormap(olc_Display, olc_WindowRoot, olc_VisualInfo->visual, AllocNone);
			olc_SetWindowAttribs.colormap = olc_ColourMap;

			// Register which events we are interested in receiving
			olc_SetWindowAttribs.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
				ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask | StructureNotifyMask;

			// Create the window
			olc_Window = XCreateWindow(olc_Display, olc_WindowRoot, vWindowPos.x, vWindowPos.y,
				vWindowSize.x, vWindowSize.y,
				0, olc_VisualInfo->depth, InputOutput, olc_VisualInfo->visual,
				CWColormap | CWEventMask, &olc_SetWindowAttribs);

			Atom wmDelete = XInternAtom(olc_Display, "WM_DELETE_WINDOW", true);
			XSetWMProtocols(olc_Display, olc_Window, &wmDelete, 1);

			XMapWindow(olc_Display, olc_Window);
			XStoreName(olc_Display, olc_Window, "OneLoneCoder.com - Pixel Game Engine");

			if (bFullScreen) // Thanks DragonEye, again :D
			{
				Atom wm_state;
				Atom fullscreen;
				wm_state = XInternAtom(olc_Display, "_NET_WM_STATE", False);
				fullscreen = XInternAtom(olc_Display, "_NET_WM_STATE_FULLSCREEN", False);
				XEvent xev{ 0 };
				xev.type = ClientMessage;
				xev.xclient.window = olc_Window;
				xev.xclient.message_type = wm_state;
				xev.xclient.format = 32;
				xev.xclient.data.l[0] = (bFullScreen ? 1 : 0);   // the action (0: off, 1: on, 2: toggle)
				xev.xclient.data.l[1] = fullscreen;             // first property to alter
				xev.xclient.data.l[2] = 0;                      // second property to alter
				xev.xclient.data.l[3] = 0;                      // source indication
				XMapWindow(olc_Display, olc_Window);
				XSendEvent(olc_Display, DefaultRootWindow(olc_Display), False,
					SubstructureRedirectMask | SubstructureNotifyMask, &xev);
				XFlush(olc_Display);
				XWindowAttributes gwa;
				XGetWindowAttributes(olc_Display, olc_Window, &gwa);
				vWindowSize.x = gwa.width;
				vWindowSize.y = gwa.height;
			}

			// Create Keyboard Mapping
			mapKeys[0x00] = Key::NONE;
			mapKeys[0x61] = Key::A; mapKeys[0x62] = Key::B; mapKeys[0x63] = Key::C; mapKeys[0x64] = Key::D; mapKeys[0x65] = Key::E;
			mapKeys[0x66] = Key::F; mapKeys[0x67] = Key::G; mapKeys[0x68] = Key::H; mapKeys[0x69] = Key::I; mapKeys[0x6A] = Key::J;
			mapKeys[0x6B] = Key::K; mapKeys[0x6C] = Key::L; mapKeys[0x6D] = Key::M; mapKeys[0x6E] = Key::N; mapKeys[0x6F] = Key::O;
			mapKeys[0x70] = Key::P; mapKeys[0x71] = Key::Q; mapKeys[0x72] = Key::R; mapKeys[0x73] = Key::S; mapKeys[0x74] = Key::T;
			mapKeys[0x75] = Key::U; mapKeys[0x76] = Key::V; mapKeys[0x77] = Key::W; mapKeys[0x78] = Key::X; mapKeys[0x79] = Key::Y;
			mapKeys[0x7A] = Key::Z;

			mapKeys[XK_F1] = Key::F1; mapKeys[XK_F2] = Key::F2; mapKeys[XK_F3] = Key::F3; mapKeys[XK_F4] = Key::F4;
			mapKeys[XK_F5] = Key::F5; mapKeys[XK_F6] = Key::F6; mapKeys[XK_F7] = Key::F7; mapKeys[XK_F8] = Key::F8;
			mapKeys[XK_F9] = Key::F9; mapKeys[XK_F10] = Key::F10; mapKeys[XK_F11] = Key::F11; mapKeys[XK_F12] = Key::F12;

			mapKeys[XK_Down] = Key::DOWN; mapKeys[XK_Left] = Key::LEFT; mapKeys[XK_Right] = Key::RIGHT; mapKeys[XK_Up] = Key::UP;
			mapKeys[XK_KP_Enter] = Key::ENTER; mapKeys[XK_Return] = Key::ENTER;

			mapKeys[XK_BackSpace] = Key::BACK; mapKeys[XK_Escape] = Key::ESCAPE; mapKeys[XK_Linefeed] = Key::ENTER;	mapKeys[XK_Pause] = Key::PAUSE;
			mapKeys[XK_Scroll_Lock] = Key::SCROLL; mapKeys[XK_Tab] = Key::TAB; mapKeys[XK_Delete] = Key::DEL; mapKeys[XK_Home] = Key::HOME;
			mapKeys[XK_End] = Key::END; mapKeys[XK_Page_Up] = Key::PGUP; mapKeys[XK_Page_Down] = Key::PGDN;	mapKeys[XK_Insert] = Key::INS;
			mapKeys[XK_Shift_L] = Key::SHIFT; mapKeys[XK_Shift_R] = Key::SHIFT; mapKeys[XK_Control_L] = Key::CTRL; mapKeys[XK_Control_R] = Key::CTRL;
			mapKeys[XK_space] = Key::SPACE; mapKeys[XK_period] = Key::PERIOD;

			mapKeys[XK_0] = Key::K0; mapKeys[XK_1] = Key::K1; mapKeys[XK_2] = Key::K2; mapKeys[XK_3] = Key::K3; mapKeys[XK_4] = Key::K4;
			mapKeys[XK_5] = Key::K5; mapKeys[XK_6] = Key::K6; mapKeys[XK_7] = Key::K7; mapKeys[XK_8] = Key::K8; mapKeys[XK_9] = Key::K9;

			mapKeys[XK_KP_0] = Key::NP0; mapKeys[XK_KP_1] = Key::NP1; mapKeys[XK_KP_2] = Key::NP2; mapKeys[XK_KP_3] = Key::NP3; mapKeys[XK_KP_4] = Key::NP4;
			mapKeys[XK_KP_5] = Key::NP5; mapKeys[XK_KP_6] = Key::NP6; mapKeys[XK_KP_7] = Key::NP7; mapKeys[XK_KP_8] = Key::NP8; mapKeys[XK_KP_9] = Key::NP9;
			mapKeys[XK_KP_Multiply] = Key::NP_MUL; mapKeys[XK_KP_Add] = Key::NP_ADD; mapKeys[XK_KP_Divide] = Key::NP_DIV; mapKeys[XK_KP_Subtract] = Key::NP_SUB; mapKeys[XK_KP_Decimal] = Key::NP_DECIMAL;

			// These keys vary depending on the keyboard. I've included comments for US and UK keyboard layouts
			mapKeys[XK_semicolon] = Key::OEM_1;		// On US and UK keyboards this is the ';:' key
			mapKeys[XK_slash] = Key::OEM_2;			// On US and UK keyboards this is the '/?' key
			mapKeys[XK_asciitilde] = Key::OEM_3;	// On US keyboard this is the '~' key
			mapKeys[XK_bracketleft] = Key::OEM_4;	// On US and UK keyboards this is the '[{' key
			mapKeys[XK_backslash] = Key::OEM_5;		// On US keyboard this is '\|' key.
			mapKeys[XK_bracketright] = Key::OEM_6;	// On US and UK keyboards this is the ']}' key
			mapKeys[XK_apostrophe] = Key::OEM_7;	// On US keyboard this is the single/double quote key. On UK, this is the single quote/@ symbol key
			mapKeys[XK_numbersign] = Key::OEM_8;	// miscellaneous characters. Varies by keyboard. I believe this to be the '#~' key on UK keyboards
			mapKeys[XK_equal] = Key::EQUALS;		// the '+' key on any keyboard
			mapKeys[XK_comma] = Key::COMMA;			// the comma key on any keyboard
			mapKeys[XK_minus] = Key::MINUS;			// the minus key on any keyboard

			mapKeys[XK_Caps_Lock] = Key::CAPS_LOCK;

			return olc::OK;
		}

		virtual olc::rcode SetWindowTitle(const std::string& s) override
		{
			X11::XStoreName(olc_Display, olc_Window, s.c_str());
			return olc::OK;
		}

		virtual olc::rcode StartSystemEventLoop() override
		{
			return olc::OK;
		}

		virtual olc::rcode HandleSystemEvent() override
		{
			using namespace X11;
			// Handle Xlib Message Loop - we do this in the
			// same thread that OpenGL was created so we dont
			// need to worry too much about multithreading with X11
			XEvent xev;
			while (XPending(olc_Display))
			{
				XNextEvent(olc_Display, &xev);
				if (xev.type == Expose)
				{
					XWindowAttributes gwa;
					XGetWindowAttributes(olc_Display, olc_Window, &gwa);
					ptrPGE->olc_UpdateWindowSize(gwa.width, gwa.height);
				}
				else if (xev.type == ConfigureNotify)
				{
					XConfigureEvent xce = xev.xconfigure;
					ptrPGE->olc_UpdateWindowSize(xce.width, xce.height);
				}
				else if (xev.type == KeyPress)
				{
					KeySym sym = XLookupKeysym(&xev.xkey, 0);
					ptrPGE->olc_UpdateKeyState(mapKeys[sym], true);
					XKeyEvent* e = (XKeyEvent*)&xev; // Because DragonEye loves numpads
					XLookupString(e, NULL, 0, &sym, NULL);
					ptrPGE->olc_UpdateKeyState(mapKeys[sym], true);
				}
				else if (xev.type == KeyRelease)
				{
					KeySym sym = XLookupKeysym(&xev.xkey, 0);
					ptrPGE->olc_UpdateKeyState(mapKeys[sym], false);
					XKeyEvent* e = (XKeyEvent*)&xev;
					XLookupString(e, NULL, 0, &sym, NULL);
					ptrPGE->olc_UpdateKeyState(mapKeys[sym], false);
				}
				else if (xev.type == ButtonPress)
				{
					switch (xev.xbutton.button)
					{
					case 1:	ptrPGE->olc_UpdateMouseState(0, true); break;
					case 2:	ptrPGE->olc_UpdateMouseState(2, true); break;
					case 3:	ptrPGE->olc_UpdateMouseState(1, true); break;
					case 4:	ptrPGE->olc_UpdateMouseWheel(120); break;
					case 5:	ptrPGE->olc_UpdateMouseWheel(-120); break;
					default: break;
					}
				}
				else if (xev.type == ButtonRelease)
				{
					switch (xev.xbutton.button)
					{
					case 1:	ptrPGE->olc_UpdateMouseState(0, false); break;
					case 2:	ptrPGE->olc_UpdateMouseState(2, false); break;
					case 3:	ptrPGE->olc_UpdateMouseState(1, false); break;
					default: break;
					}
				}
				else if (xev.type == MotionNotify)
				{
					ptrPGE->olc_UpdateMouse(xev.xmotion.x, xev.xmotion.y);
				}
				else if (xev.type == FocusIn)
				{
					ptrPGE->olc_UpdateKeyFocus(true);
				}
				else if (xev.type == FocusOut)
				{
					ptrPGE->olc_UpdateKeyFocus(false);
				}
				else if (xev.type == ClientMessage)
				{
					ptrPGE->olc_Terminate();
				}
			}
			return olc::OK;
		}
	};
}
#endif
// O------------------------------------------------------------------------------O
// | END PLATFORM: LINUX                                                          |
// O------------------------------------------------------------------------------O

// O------------------------------------------------------------------------------O
// | START PLATFORM: GLUT (used to make it simple for Apple)                      |
// O------------------------------------------------------------------------------O
//
// VERY IMPORTANT!!! The Apple port was originally created by @Mumflr (discord)
// and the repo for the development of this project can be found here:
// https://github.com/MumflrFumperdink/olcPGEMac which contains maccy goodness
// and support on how to setup your build environment.
//
// "MASSIVE MASSIVE THANKS TO MUMFLR" - Javidx9
#if defined(OLC_PLATFORM_GLUT)
namespace olc {
	class Platform_GLUT : public olc::Platform
	{
	public:
		static std::atomic<bool>* bActiveRef;

		virtual olc::rcode ApplicationStartUp() override {
			return olc::rcode::OK;
		}

		virtual olc::rcode ApplicationCleanUp() override
		{
			return olc::rcode::OK;
		}

		virtual olc::rcode ThreadStartUp() override
		{
			return olc::rcode::OK;
		}

		virtual olc::rcode ThreadCleanUp() override
		{
			renderer->DestroyDevice();
			return olc::OK;
		}

		virtual olc::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc::vi2d& vViewPos, const olc::vi2d& vViewSize) override
		{
			if (renderer->CreateDevice({}, bFullScreen, bEnableVSYNC) == olc::rcode::OK)
			{
				renderer->UpdateViewport(vViewPos, vViewSize);
				return olc::rcode::OK;
			}
			else
				return olc::rcode::FAIL;
		}

		static void ExitMainLoop() {
			if (!ptrPGE->OnUserDestroy()) {
				*bActiveRef = true;
				return;
			}
			platform->ThreadCleanUp();
			platform->ApplicationCleanUp();
			exit(0);
		}

		static void ThreadFunct() {
			if (!*bActiveRef) {
				ExitMainLoop();
				return;
			}
			glutPostRedisplay();
		}

		static void DrawFunct() {
			ptrPGE->olc_CoreUpdate();
		}

		virtual olc::rcode CreateWindowPane(const olc::vi2d& vWindowPos, olc::vi2d& vWindowSize, bool bFullScreen) override
		{
			renderer->PrepareDevice();

			if (bFullScreen)
			{
				vWindowSize.x = glutGet(GLUT_SCREEN_WIDTH);
				vWindowSize.y = glutGet(GLUT_SCREEN_HEIGHT);
				glutFullScreen();
			}

			if (vWindowSize.x > glutGet(GLUT_SCREEN_WIDTH) || vWindowSize.y > glutGet(GLUT_SCREEN_HEIGHT)) {
				perror("ERROR: The specified window dimensions do not fit on your screen\n");
				return olc::FAIL;
			}

			// Create Keyboard Mapping
			mapKeys[0x00] = Key::NONE;
			mapKeys['A'] = Key::A; mapKeys['B'] = Key::B; mapKeys['C'] = Key::C; mapKeys['D'] = Key::D; mapKeys['E'] = Key::E;
			mapKeys['F'] = Key::F; mapKeys['G'] = Key::G; mapKeys['H'] = Key::H; mapKeys['I'] = Key::I; mapKeys['J'] = Key::J;
			mapKeys['K'] = Key::K; mapKeys['L'] = Key::L; mapKeys['M'] = Key::M; mapKeys['N'] = Key::N; mapKeys['O'] = Key::O;
			mapKeys['P'] = Key::P; mapKeys['Q'] = Key::Q; mapKeys['R'] = Key::R; mapKeys['S'] = Key::S; mapKeys['T'] = Key::T;
			mapKeys['U'] = Key::U; mapKeys['V'] = Key::V; mapKeys['W'] = Key::W; mapKeys['X'] = Key::X; mapKeys['Y'] = Key::Y;
			mapKeys['Z'] = Key::Z;

			mapKeys[GLUT_KEY_F1] = Key::F1; mapKeys[GLUT_KEY_F2] = Key::F2; mapKeys[GLUT_KEY_F3] = Key::F3; mapKeys[GLUT_KEY_F4] = Key::F4;
			mapKeys[GLUT_KEY_F5] = Key::F5; mapKeys[GLUT_KEY_F6] = Key::F6; mapKeys[GLUT_KEY_F7] = Key::F7; mapKeys[GLUT_KEY_F8] = Key::F8;
			mapKeys[GLUT_KEY_F9] = Key::F9; mapKeys[GLUT_KEY_F10] = Key::F10; mapKeys[GLUT_KEY_F11] = Key::F11; mapKeys[GLUT_KEY_F12] = Key::F12;

			mapKeys[GLUT_KEY_DOWN] = Key::DOWN; mapKeys[GLUT_KEY_LEFT] = Key::LEFT; mapKeys[GLUT_KEY_RIGHT] = Key::RIGHT; mapKeys[GLUT_KEY_UP] = Key::UP;
			mapKeys[13] = Key::ENTER;

			mapKeys[127] = Key::BACK; mapKeys[27] = Key::ESCAPE;
			mapKeys[9] = Key::TAB;  mapKeys[GLUT_KEY_HOME] = Key::HOME;
			mapKeys[GLUT_KEY_END] = Key::END; mapKeys[GLUT_KEY_PAGE_UP] = Key::PGUP; mapKeys[GLUT_KEY_PAGE_DOWN] = Key::PGDN;    mapKeys[GLUT_KEY_INSERT] = Key::INS;
			mapKeys[32] = Key::SPACE; mapKeys[46] = Key::PERIOD;

			mapKeys[48] = Key::K0; mapKeys[49] = Key::K1; mapKeys[50] = Key::K2; mapKeys[51] = Key::K3; mapKeys[52] = Key::K4;
			mapKeys[53] = Key::K5; mapKeys[54] = Key::K6; mapKeys[55] = Key::K7; mapKeys[56] = Key::K8; mapKeys[57] = Key::K9;

			// NOTE: MISSING KEYS :O

			glutKeyboardFunc([](unsigned char key, int x, int y) -> void {
				switch (glutGetModifiers()) {
				case 0: //This is when there are no modifiers
					if ('a' <= key && key <= 'z') key -= 32;
					break;
				case GLUT_ACTIVE_SHIFT:
					ptrPGE->olc_UpdateKeyState(Key::SHIFT, true);
					break;
				case GLUT_ACTIVE_CTRL:
					if ('a' <= key && key <= 'z') key -= 32;
					ptrPGE->olc_UpdateKeyState(Key::CTRL, true);
					break;
				case GLUT_ACTIVE_ALT:
					if ('a' <= key && key <= 'z') key -= 32;
					break;
				}

				if (mapKeys[key])
					ptrPGE->olc_UpdateKeyState(mapKeys[key], true);
				});

			glutKeyboardUpFunc([](unsigned char key, int x, int y) -> void {
				switch (glutGetModifiers()) {
				case 0: //This is when there are no modifiers
					if ('a' <= key && key <= 'z') key -= 32;
					break;
				case GLUT_ACTIVE_SHIFT:
					ptrPGE->olc_UpdateKeyState(Key::SHIFT, false);
					break;
				case GLUT_ACTIVE_CTRL:
					if ('a' <= key && key <= 'z') key -= 32;
					ptrPGE->olc_UpdateKeyState(Key::CTRL, false);
					break;
				case GLUT_ACTIVE_ALT:
					if ('a' <= key && key <= 'z') key -= 32;
					//No ALT in PGE
					break;
				}

				if (mapKeys[key])
					ptrPGE->olc_UpdateKeyState(mapKeys[key], false);
				});

			//Special keys
			glutSpecialFunc([](int key, int x, int y) -> void {
				if (mapKeys[key])
					ptrPGE->olc_UpdateKeyState(mapKeys[key], true);
				});

			glutSpecialUpFunc([](int key, int x, int y) -> void {
				if (mapKeys[key])
					ptrPGE->olc_UpdateKeyState(mapKeys[key], false);
				});

			glutMouseFunc([](int button, int state, int x, int y) -> void {
				switch (button) {
				case GLUT_LEFT_BUTTON:
					if (state == GLUT_UP) ptrPGE->olc_UpdateMouseState(0, false);
					else if (state == GLUT_DOWN) ptrPGE->olc_UpdateMouseState(0, true);
					break;
				case GLUT_MIDDLE_BUTTON:
					if (state == GLUT_UP) ptrPGE->olc_UpdateMouseState(2, false);
					else if (state == GLUT_DOWN) ptrPGE->olc_UpdateMouseState(2, true);
					break;
				case GLUT_RIGHT_BUTTON:
					if (state == GLUT_UP) ptrPGE->olc_UpdateMouseState(1, false);
					else if (state == GLUT_DOWN) ptrPGE->olc_UpdateMouseState(1, true);
					break;
				}
				});

			auto mouseMoveCall = [](int x, int y) -> void {
				ptrPGE->olc_UpdateMouse(x, y);
			};

			glutMotionFunc(mouseMoveCall);
			glutPassiveMotionFunc(mouseMoveCall);

			glutEntryFunc([](int state) -> void {
				if (state == GLUT_ENTERED) ptrPGE->olc_UpdateKeyFocus(true);
				else if (state == GLUT_LEFT) ptrPGE->olc_UpdateKeyFocus(false);
				});

			glutDisplayFunc(DrawFunct);
			glutIdleFunc(ThreadFunct);

			return olc::OK;
		}

		virtual olc::rcode SetWindowTitle(const std::string& s) override
		{
			glutSetWindowTitle(s.c_str());
			return olc::OK;
		}

		virtual olc::rcode StartSystemEventLoop() override {
			glutMainLoop();
			return olc::OK;
		}

		virtual olc::rcode HandleSystemEvent() override
		{
			return olc::OK;
		}
	};

	std::atomic<bool>* Platform_GLUT::bActiveRef{ nullptr };

	//Custom Start
	olc::rcode PixelGameEngine::Start()
	{
		if (platform->ApplicationStartUp() != olc::OK) return olc::FAIL;

		// Construct the window
		if (platform->CreateWindowPane({ 30,30 }, vWindowSize, bFullScreen) != olc::OK) return olc::FAIL;
		olc_UpdateWindowSize(vWindowSize.x, vWindowSize.y);

		if (platform->ThreadStartUp() == olc::FAIL)  return olc::FAIL;

		olc_PrepareEngine();

		if (!OnUserCreate()) return olc::FAIL;

		Platform_GLUT::bActiveRef = &bAtomActive;

		glutWMCloseFunc(Platform_GLUT::ExitMainLoop);

		bAtomActive = true;

		platform->StartSystemEventLoop();

		//This code will not even be run but why not
		if (platform->ApplicationCleanUp() != olc::OK) return olc::FAIL;

		return olc::OK;
	}
}

#endif
// O------------------------------------------------------------------------------O
// | END PLATFORM: GLUT                                                           |
// O------------------------------------------------------------------------------O

namespace olc
{
	void PixelGameEngine::olc_ConfigureSystem()
	{
#if defined(OLC_IMAGE_GDI)
		Sprite::loader = std::make_unique<ImageLoader_GDIPlus>();
#endif

#if defined(OLC_IMAGE_LIBPNG)
		olc::Sprite::loader = std::make_unique<olc::ImageLoader_LibPNG>();
#endif

#if defined(OLC_IMAGE_STB)
		olc::Sprite::loader = std::make_unique<olc::ImageLoader_STB>();
#endif

#if defined(OLC_PLATFORM_WINAPI)
		platform = std::make_unique<Platform_Windows>();
#endif

#if defined(OLC_PLATFORM_X11)
		platform = std::make_unique<olc::Platform_Linux>();
#endif

#if defined(OLC_PLATFORM_GLUT)
		platform = std::make_unique<olc::Platform_GLUT>();
#endif

#if defined(OLC_GFX_OPENGL10)
		renderer = std::make_unique<Renderer_OGL10>();
#endif

#if defined(OLC_GFX_OPENGL33)
		renderer = std::make_unique<olc::Renderer_OGL33>();
#endif

#if defined(OLC_GFX_OPENGLES2)
		renderer = std::make_unique<olc::Renderer_OGLES2>();
#endif

#if defined(OLC_GFX_DIRECTX10)
		renderer = std::make_unique<olc::Renderer_DX10>();
#endif

#if defined(OLC_GFX_DIRECTX11)
		renderer = std::make_unique<olc::Renderer_DX11>();
#endif

		// Associate components with PGE instance
		platform->ptrPGE = this;
		renderer->ptrPGE = this;
	}
}
