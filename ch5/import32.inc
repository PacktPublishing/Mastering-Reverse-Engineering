
include 'elf.inc'

macro interpreter [library]
{
 segment interpreter readable
 db library,0
}

macro needed [library]
{
 local str
 match needed,needed@dynamic \{ define needed@dynamic needed,str:library \}
 match ,needed@dynamic \{ define needed@dynamic str:library \}
}
define needed@dynamic

macro import [name]
{
 common
  local strtab,strsz,symtab,rel,relsz,hash
  segment dynamic readable
  match needed,needed@dynamic
  \{ irp item,needed \\{ match str:library,item \\\{ dd DT_NEEDED,str-strtab \\\} \\} \}
  dd DT_STRTAB,strtab
  dd DT_STRSZ,strsz
  dd DT_SYMTAB,symtab
  dd DT_SYMENT,sizeof.Elf32_Sym
  dd DT_REL,rel
  dd DT_RELSZ,relsz
  dd DT_RELENT,sizeof.Elf32_Rel
  dd DT_HASH,hash
  dd DT_NULL,0
  segment readable writeable
  symtab: Elf32_Sym
 forward
  local fstr
  Elf32_Sym fstr-strtab,0,0,STB_GLOBAL,STT_FUNC,0,0
 common
  rel:
  local counter
  counter = 1
 forward
   Elf32_Rel name,counter,R_386_32
   counter = counter+1
 common
  relsz = $-rel
  hash:
  dd 1,counter
  dd 0
  repeat counter
   if %=counter
    dd 0
   else
    dd %
   end if
  end repeat
  strtab db 0
 forward
  fstr db `name,0
 common
  match needed,needed@dynamic
  \{ irp item,needed \\{ match str:library,item \\\{ str db library,0 \\\} \\} \}
  strsz = $-strtab
 forward
  name dd 0
}
