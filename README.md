
โปรแกรมนี้เป็นผลเฉลยของสมการลากรองจ์ (Lagrange's Equation) ที่ใช้แก้ระบบเพนดูลัมคู่

### วิธีติดตั้ง
 1. Clone repository 
```bash
git clone https://github.com/Quackudy/Double-Pendulum-in-SFML
```
2. สร้าง Solution ด้วย Cmake
```bash
   mkdir build
   cd build
   cmake ..
```
3. เปิด Solution และ build


### ต้องแก้อะไรต่อ??
  - หากลองรันไปเรื่อย ๆ จะพบว่าระบบมีพลังงานกลเพิ่มมากขึ้นเรื่อย ๆ ในตอนแรกได้ใช้ Euler Integration จากนั้นเปลี่ยนมาใช้ Runge-Kutta Integration แต่ก็ยังคงเกิด Instability

### Credit
https://youtu.be/tc2ah-KnDXw?si=H7fkXBVDOv1tJMGm



https://github.com/user-attachments/assets/af82a8b5-8f10-4446-bf65-3d8c840f900e
