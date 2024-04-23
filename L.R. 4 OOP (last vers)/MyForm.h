#pragma once
#include "Container.h"
namespace LR4OOPlastvers {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	static circles cont;
	static int fCtrl = 0;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pBox;
	private: System::Windows::Forms::CheckBox^ cBoxCtrl;
	private: System::Windows::Forms::CheckBox^ cBoxMulty;
	protected:

	protected:



	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pBox = (gcnew System::Windows::Forms::PictureBox());
			this->cBoxCtrl = (gcnew System::Windows::Forms::CheckBox());
			this->cBoxMulty = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pBox))->BeginInit();
			this->SuspendLayout();
			// 
			// pBox
			// 
			this->pBox->BackColor = System::Drawing::Color::White;
			this->pBox->Location = System::Drawing::Point(0, 0);
			this->pBox->Name = L"pBox";
			this->pBox->Size = System::Drawing::Size(697, 433);
			this->pBox->TabIndex = 0;
			this->pBox->TabStop = false;
			this->pBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pBox_Paint);
			this->pBox->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pBox_MouseClick);
			// 
			// cBoxCtrl
			// 
			this->cBoxCtrl->AutoSize = true;
			this->cBoxCtrl->Location = System::Drawing::Point(13, 13);
			this->cBoxCtrl->Name = L"cBoxCtrl";
			this->cBoxCtrl->Size = System::Drawing::Size(198, 20);
			this->cBoxCtrl->TabIndex = 1;
			this->cBoxCtrl->Text = L"¬ключить функционал ctrl";
			this->cBoxCtrl->UseVisualStyleBackColor = true;
			// 
			// cBoxMulty
			// 
			this->cBoxMulty->AutoSize = true;
			this->cBoxMulty->Location = System::Drawing::Point(13, 40);
			this->cBoxMulty->Name = L"cBoxMulty";
			this->cBoxMulty->Size = System::Drawing::Size(324, 20);
			this->cBoxMulty->TabIndex = 2;
			this->cBoxMulty->Text = L"¬ыделить несколько кругов по одному клику";
			this->cBoxMulty->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(694, 431);
			this->Controls->Add(this->cBoxMulty);
			this->Controls->Add(this->cBoxCtrl);
			this->Controls->Add(this->pBox);
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
private: System::Void pBox_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		cont.resetCurrent();
		int x = e->X;
		int y = e->Y;
		CCircle* cur;
		int counter = 0;
		Graphics^ g = pBox->CreateGraphics();
		for (int i = 0; i < cont.getSize(); i++) {
			cur = cont.getCurrent();
			if (cur->isPointInC(x, y)) counter++;
			cont.next();
		}
		if (counter == 0) {
			cont.unselect(g);
			CCircle* c = new CCircle(x, y, true);
			CCircle* l = cont.getLast();
			if (l != nullptr) {
				l->Bleach(g);
				l->setIsSlctd(false);
				l->Draw(g);
			}
			c->Draw(g);
			cont.push_back(c);
		}
		else if (counter > 0) {
			cont.resetCurrent();
			if (fCtrl == 0) cont.unClick(g);
			cont.resetCurrent();
			if (e->Button == System::Windows::Forms::MouseButtons::Left) {
				for (int i = 0; i < cont.getSize(); i++) {
					CCircle* cur = cont.getCurrent();
					if (cur->isPointInC(x, y)) {
						cur->Bleach(g);
						cur->setIsSlctd(true);
						cur->isClicked = true;
						cur->Draw(g);
						if (!(cBoxMulty->Checked)) break;
					}
					cont.next();
				}
			}
		}
	}
	private: System::Void pBox_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = pBox->CreateGraphics();
		cont.DrawAll(g);
	}
private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	Graphics^ g = pBox->CreateGraphics();
	if (e->KeyCode == Keys::ControlKey && cBoxCtrl->Checked) {
		fCtrl = 1;
	}
	else if (e->KeyCode == Keys::Delete) {
		cont.deleteSlctd(g);
		cont.DrawAll(g);
		
	}
}
private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (e->KeyCode == Keys::ControlKey && cBoxCtrl->Checked) {
		fCtrl = 0;
	}
}
	 
};
}
