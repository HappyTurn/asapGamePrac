#include "CModel.h"

CModel::CModel(LPCWSTR path) {
	this->_scale = 1.0f;
	D3DXLoadMeshFromX(
		path,
		D3DXMESH_SYSTEMMEM,
		this->getDevice(),
		NULL,
		&_materialBuffer,         // �}�e���A�������w���|�C���^�̃A�h���X
		NULL,
		&_numOfMat,        // �}�e���A�������Ԃ��Ă���
		&_mesh
		);

	if (_mesh == NULL) {
		std::cout << "X FILE LOAD ERROR" << std::endl;
	}
	else {
		std::cout << "X FILE LODED" << std::endl;
	}
}

CModel::~CModel() {

}


HRESULT CModel::draw() {
	if (this->_mesh == NULL) {
		std::cout << "X FILE DRAW ERROR" << std::endl;
		return E_FAIL;
	}

	D3DXMatrixIdentity(&_modelMatrix);

	// ���f���̊g��E�k�����s��ɉ�����
	D3DXMatrixIdentity(&_scaleMatrix);
	D3DXMatrixScaling(&_scaleMatrix, _scale, _scale, _scale);
	_modelMatrix *= _scaleMatrix;

	// ���f���̉�]���s��ɉ�����
	D3DXMatrixIdentity(&_rotateMatrix);
	D3DXMatrixRotationYawPitchRoll(&_rotateMatrix, _rotVec.x, _rotVec.y, _rotVec.z);
	_modelMatrix *= _rotateMatrix;

	// ���f���̕��s�ړ����s��ɉ�����
	D3DXMatrixIdentity(&_translateMatrix);
	D3DXMatrixTranslation(&_translateMatrix, _posVec.x, _posVec.y, _posVec.z);
	_modelMatrix *= _translateMatrix;

	// ���[���h�s��ɓK�p
	this->getDevice()->SetTransform(D3DTS_WORLD, &_modelMatrix);

	/*
	D3DXMATERIAL*	d3Mat = (D3DXMATERIAL*)_materialBuffer->GetBufferPointer();
	_material = new D3DMATERIAL9[_numOfMat];
	_texture = new LPDIRECT3DTEXTURE9[_numOfMat];
	for (int i = 0; i < _numOfMat; i++) {
	_material[i] = d3Mat[i].MatD3D;
	_material[i].Ambient = _material[i].Diffuse;// ����������
	_texture[i] = NULL;	// �e�N�X�`��������
	// �g�p���Ă���e�N�X�`��������Γǂݍ���
	if (d3Mat[i].pTextureFilename != NULL &&
	lstrlen((LPCWSTR)d3Mat[i].pTextureFilename) > 0)
	{
	// �e�N�X�`���ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(
	this->getDevice(),
	(LPCWSTR)d3Mat[i].pTextureFilename,
	&_texture[i])))
	{
	return E_FAIL;
	}
	}
	}

	_materialBuffer->Release();



	for (int i = 0; i < _numOfMat; i++)
	{
	this->getDevice()->SetMaterial(&_material[i]);	// �}�e���A�������Z�b�g
	this->getDevice()->SetTexture(0, _texture[i]);	// �e�N�X�`�������Z�b�g
	_mesh->DrawSubset(i);	// ���b�V����`��
	}
	*/


	this->_mesh->DrawSubset(0);
	return S_OK;
}


void CModel::updateScale(float scale) {
	this->_scale += scale;
}

void CModel::updateRotate(D3DXVECTOR3 vec) {
	this->_rotVec += vec;
}

void CModel::updatePosition(D3DXVECTOR3 vec) {
	this->_posVec += vec;
}

void CModel::setScale(float scale) {
	this->_scale = scale;
}

void CModel::setRotate(D3DXVECTOR3 vec) {
	this->_rotVec = vec;
}

void CModel::setPosition(D3DXVECTOR3 vec) {
	this->_posVec = vec;
}