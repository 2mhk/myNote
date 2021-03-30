connect(mySpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), mySlider, &QSlider::setValue);

