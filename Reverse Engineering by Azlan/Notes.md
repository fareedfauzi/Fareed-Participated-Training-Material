# Why programming is a must in reverse engineering?
- Most of the time, reverse engineering required scripting to create our own tools.
- In order to analysis (understand) other people/programmer's codes, we must get into their head meaning that we must think like their brain.
- Kita belajar programming not as programmer yang hari2 tengok coding, but we master programming to understand people code

# Why we need to learn PE file?
- Because most of malware adalah packed. Nak faham packed PE, kena faham structure PE file

# How to unpack?
- Execute first
- Tgk running tak
- Kalau tak running, tengok kat mana dia sangkut
- Analyse kalau ada anti-vm, anti-debug etc.
- Then guna tools (dump etc.)

# Reverse engineering punya learning curve
- Akan mencanak expertise kita bila kita master programming, assembly, os api, pe file and etc. But required time.
- If kita focus betul2 in 5 years, kita boleh jadi expert.

# Tips
- Kena ada curiousity yang tinggi how things works.

# Calculate RVA
RVA = VA - Image Base

# Calculate offset
File offset = rva (virtual offset) - va + raw offset(section)
