#pragma once
#include <Siv3D.hpp>

class ObjData
{
public:
	inline static ObjData& getInstance()
	{
		if (!_instance) {
			_instance = new ObjData();
		}
		return *_instance;
	}

	// ����
	inline String name(const int32& value ) const				{ return Parse<String>(_data[value][static_cast <int32>(Info::Name)]); }
	inline String texturePass(const int32& value) const			{ return Parse<String>(_data[value][static_cast <int32>(Info::Texture)]); }
	inline Size textureWH(const int32& value) const				{ return Parse<Size>(_data[value][static_cast <int32>(Info::TextureWH)]); }
	inline Size textureAllCharaNumXY(const int32& value) const	{ return Parse<Size>(_data[value][static_cast <int32>(Info::TextureAllCharaNumXY)]); }
	inline Size textureCharaNum(const int32& value) const		{ return Parse<Size>(_data[value][static_cast <int32>(Info::TextureCharaNum)]); }
	inline Size textureTileXYNum(const int32& value) const		{ return Parse<Size>(_data[value][static_cast <int32>(Info::TextureTileXYNum)]); }
	inline Size textureWalkTileXYNum(const int32& value) const	{ return Parse<Size>(_data[value][static_cast <int32>(Info::TextureWalkTileXYNum)]); }
	inline Size textureAttackTileXYNum(const int32& value) const{ return Parse<Size>(_data[value][static_cast <int32>(Info::TextureAttackTileXYNum)]); }
	inline Size textureTileWH(const int32& value) const			{ return Parse<Size>(_data[value][static_cast <int32>(Info::TextureTileWH)]); }
	inline Size collisionSize(const int32& value) const			{ return Parse<Size>(_data[value][static_cast <int32>(Info::CollisionSize)]); }
	inline Vec2 collisionMargin(const int32& value) const		{ return Parse<Size>(_data[value][static_cast <int32>(Info::CollisionMargin)]); }
	inline Size collisionForMoveSize(const int32& value) const	{ return Parse<Size>(_data[value][static_cast <int32>(Info::CollisionForMoveSize)]); }
	inline Vec2 collisionForMoveMargin(const int32& value) const{ return Parse<Size>(_data[value][static_cast <int32>(Info::CollisionForMoveMargin)]); }
	inline String type(const int32& value) const				{ return Parse<String>(_data[value][static_cast <int32>(Info::Type)]); }
	
	// �퓬�n�I�u�W�F�N�g
	inline int32 level(const int32& value) const			{ return Parse<int32>(_data[value][static_cast <int32>(Info::Level)]); }
	inline int32 currentExp(const int32& value) const		{ return Parse<int32>(_data[value][static_cast <int32>(Info::CurrentExp)]); }
	inline int32 nextExp(const int32& value) const			{ return Parse<int32>(_data[value][static_cast <int32>(Info::NextExp)]); }
	inline int32 hp(const int32& value) const				{ return Parse<int32>(_data[value][static_cast <int32>(Info::Hp)]); }
	inline int32 mp(const int32& value) const				{ return Parse<int32>(_data[value][static_cast <int32>(Info::Mp)]); }
	inline int32 attack(const int32& value) const			{ return Parse<int32>(_data[value][static_cast <int32>(Info::Attack)]); }
	inline int32 defense(const int32& value) const			{ return Parse<int32>(_data[value][static_cast <int32>(Info::Defense)]); }
	inline int32 agility(const int32& value) const			{ return Parse<int32>(_data[value][static_cast <int32>(Info::Agility)]); }
	inline int32 intel(const int32& value) const			{ return Parse<int32>(_data[value][static_cast <int32>(Info::Intel)]); }
	inline int32 resist(const int32& value) const			{ return Parse<int32>(_data[value][static_cast <int32>(Info::Resist)]); }
	inline int32 state(const int32& value) const			{ return Parse<int32>(_data[value][static_cast <int32>(Info::State)]); }
	inline int32 parsonality(const int32& value) const		{ return Parse<int32>(_data[value][static_cast <int32>(Info::Parsonality)]); }

	// �A�C�e��

private:
	ObjData();
	static ObjData* _instance;
	const CSVData _data;

	enum class Info
	{
		VALUE = 0,					// �I�u�W�F�N�g�i���o�[
		Name,						// ���O
		Texture,					// �e�N�X�`���p�X
		TextureWH,					// �e�N�X�`���̃T�C�Y
		TextureAllCharaNumXY,		// �e�N�X�`���̃L������
		TextureCharaNum,			// �e�N�X�`������ΏۂƂ���L�����ԍ�
		TextureTileXYNum,			// �P�L�����̃^�C����
		TextureWalkTileXYNum,		// �P�L�����̈ړ����[�V�����^�C����
		TextureAttackTileXYNum,		// �P�L�����̍U�����[�V�����^�C����
		TextureTileWH,				// �P�^�C���̃T�C�Y
		CollisionSize,				// �R���W�����̈�i�U���E�b��etc...�j
		CollisionMargin,			// �R���W�����̈�J�n�ʒu�����p�i�f�t�H���g�FXY�L���������j
		CollisionForMoveSize,		// �ړ��p�R���W�����̈�
		CollisionForMoveMargin,		// �ړ��p�R���W�����J�n�ʒu�����p�i�f�t�H���g�FX����, Y��Ӂj
		Type,						
		Level,						
		CurrentExp,					
		NextExp,					
		Hp,							
		Mp,							
		Attack,						
		Defense,					
		Agility,						
		Intel,					
		Resist,					
		State,						
		Parsonality					
	};
};

