#include "SliderBar.h"

SliderBar * SliderBar::createSliderBar(const char * sliderFileName,const char * backgroundFileName,CCSize bgSize,float multiple){
	SliderBar * pRet=new SliderBar();
	if (pRet && pRet->init(sliderFileName, backgroundFileName,bgSize,multiple)) {
		pRet->autorelease();
		return pRet;
	}
	else
		CC_SAFE_DELETE(pRet);
	return NULL;
}

SliderBar::SliderBar(){
}
SliderBar::~SliderBar(){
}
bool SliderBar::init(const char * sliderFileName,const char * backgroundFileName,Size bgSize,float multiple){
	/* ��ʼ������ */
	_bgSize=bgSize;
	/* һ��Ҫʹ�þŹ����� */
	m_backgroundSprite=Scale9Sprite::create(backgroundFileName);
	m_backgroundSprite->setContentSize(Size( m_backgroundSprite->getContentSize().width, bgSize.height));
	this->addChild(m_backgroundSprite);
	m_sliderSprite=Scale9Sprite::create(sliderFileName);
	m_sliderSprite->setContentSize(bgSize/multiple);
	this->addChild(m_sliderSprite);
	_beginPos=ccp(-_bgSize.width/2 + m_sliderSprite->getContentSize().width/2,0);
	_endPos= ccp(_bgSize.width/2 - m_sliderSprite->getContentSize().width/2,0);
	m_sliderSprite->setPosition(_beginPos);

	_sdSize=m_sliderSprite->getContentSize();
	return true;
}

void SliderBar::setValue(float value){
	/* �������䷶Χ� */
	if (value>=0 && value<=1) {
		/* ��������λ�� */
		m_sliderSprite->setPosition(ccp(_beginPos.x+(_endPos.x-_beginPos.x) * value , 0));
	}
	/* ����������� */
	else if (value<0){
		/* �������ô�С��λ�� */
		m_sliderSprite->setContentSize(CCSize(_sdSize.width+value *_sdSize.width,_sdSize.height));
		m_sliderSprite->setPosition(ccp(_beginPos.x+value *_sdSize.width/2, 0));
	}
	/* ���������Ҳ� */
	else if (value>1){
		/* �������ô�С��λ�� */
		m_sliderSprite->setContentSize(CCSize(_sdSize.width+(1-value) *_sdSize.width,_sdSize.height));
		m_sliderSprite->setPosition(ccp(_endPos.x-(1-value) *_sdSize.width/2, 0));
	}

}