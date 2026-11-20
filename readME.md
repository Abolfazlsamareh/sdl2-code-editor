<div align="center">

# 💻 SDL2 Code Editor

**یک محیط ویرایشگر کد گرافیکی، سبک و سریع ساخته‌شده با C++ و کتابخانه SDL2**

![C++](https://img.shields.io/badge/C++-17%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![SDL2](https://img.shields.io/badge/SDL2-Graphics-blue?style=for-the-badge)
![SDL2_ttf](https://img.shields.io/badge/SDL2__ttf-Font_Rendering-orange?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

</div>

---

## ✨ ویژگی‌ها

- 🎨 **رنگ‌آمیزی هوشمند کد (Syntax Highlighting):** تشخیص و رنگ‌آمیزی خودکار کلمات کلیدی (`int`, `float`, `double`, `class`, `if`, `while`, `#include`)، رشته‌ها، کاراکترها، اعداد، عملگرها، پرانتزها، نام توابع، متغیرها و کامنت‌ها (`//`).
- 🌓 **دو تم گرافیکی (Light & Dark Mode):** قابلیت جابه‌جایی سریع بین پس‌زمینه روشن و تاریک با یک کلیک از نوار ابزار بالا.
- 🔢 **شماره‌گذاری خطوط (Line Numbers):** نمایش خودکار شماره هر خط در حاشیه سمت چپ ویرایشگر.
- 🖱️ **اسکرول عمودی و افقی:** پشتیبانی از اسکرول ماوس و حرکت روان در خطوط طولانی.
- ⌨️ **تکمیل خودکار نمادها (Auto-Closing):** بستن خودکار پرانتز `()`، آکولاد `{}`، براکت `[]` و کوتیشن‌ها `""` و `''` هنگام تایپ.
- 📁 **مدیریت پروژه:** امکان ایجاد پروژه جدید با نام دلخواه و ذخیره‌سازی مستقیم فایل کد در مسیر مشخص‌شده.

---

## 🛠️ پیش‌نیازها

برای کامپایل و اجرای این پروژه به موارد زیر نیاز دارید:

- کامپایلر **C++** (مانند MinGW یا MSVC)
- کتابخانه **SDL2**
- کتابخانه **SDL2_ttf**
- فونت **Consolas** در مسیر پیش‌فرض ویندوز (`C:/Windows/Fonts/consola.ttf`)

---

## 🚀 نصب و اجرا

1. **کلون کردن مخزن:**
   ```bash
   git clone [https://github.com/your-username/sdl2-code-editor.git](https://github.com/your-username/sdl2-code-editor.git)
   cd sdl2-code-editor