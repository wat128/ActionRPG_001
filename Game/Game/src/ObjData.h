#pragma once
#include <Siv3D.hpp>

class ObjData
{
public:
	inline static ObjData* getInstance()
	{
		if (!_instance) {
			_instance = new ObjData();
		}
		return _instance;
	}

	// ����
	inline String Name(const int32& value ) const		{ return Parse<String>(_data[value][static_cast <int32>(Info::Name)]); }
	inline String TexturePass(const int32& value) const	{ return Parse<String>(_data[value][static_cast <int32>(Info::Texture)]); }
	inline int32 RegionW(const int32& value) const		{ return Parse<int32>(_data[value][static_cast <int32>(Info::RegionW)]); }
	inline int32 RegionH(const int32& value) const		{ return Parse<int32>(_data[value][static_cast <int32>(Info::RegionH)]); }
	inline String Type(const int32& value) const		{ return Parse<String>(_data[value][static_cast <int32>(Info::Type)]); }
	
	// �퓬�n�I�u�W�F�N�g
	inline int32 Level(const int32& value) const		{ return Parse<int32>(_data[value][static_cast <int32>(Info::Level)]); }
	inline int32 CurrentExp(const int32& value) const	{ return Parse<int32>(_data[value][static_cast <int32>(Info::CurrentExp)]); }
	inline int32 NextExp(const int32& value) const		{ return Parse<int32>(_data[value][static_cast <int32>(Info::NextExp)]); }
	inline int32 Hp(const int32& value) const			{ return Parse<int32>(_data[value][static_cast <int32>(Info::Hp)]); }
	inline int32 Mp(const int32& value) const			{ return Parse<int32>(_data[value][static_cast <int32>(Info::Mp)]); }
	inline int32 Power(const int32& value) const		{ return Parse<int32>(_data[value][static_cast <int32>(Info::Power)]); }
	inline int32 Physical(const int32& value) const		{ return Parse<int32>(_data[value][static_cast <int32>(Info::Physical)]); }
	inline int32 Speed(const int32& value) const		{ return Parse<int32>(_data[value][static_cast <int32>(Info::Speed)]); }
	inline int32 Knowledge(const int32& value) const	{ return Parse<int32>(_data[value][static_cast <int32>(Info::Knowledge)]); }
	inline int32 State(const int32& value) const		{ return Parse<int32>(_data[value][static_cast <int32>(Info::State)]); }
	inline int32 Parsonality(const int32& value) const	{ return Parse<int32>(_data[value][static_cast <int32>(Info::Parsonality)]); }

	// �A�C�e��

private:
	ObjData();
	static ObjData* _instance;
	const CSVData _data;

	enum class Info
	{
		VALUE = 0,
		Name,
		Texture,
		RegionW,
		RegionH,
		Type,
		Level,
		CurrentExp,
		NextExp,
		Hp,
		Mp,
		Power,
		Physical,
		Speed,
		Knowledge,
		State,
		Parsonality
	};
};

