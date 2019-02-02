
mov-cmp:     file format elf32-i386


Disassembly of section .text:

00060000 <start>:
   60000:	e9 00 00 00 00       	jmp    60005 <main>

00060005 <main>:
   60005:	b8 00 00 00 00       	mov    $0x0,%eax
   6000a:	bb 01 00 00 00       	mov    $0x1,%ebx
   6000f:	b9 00 00 00 00       	mov    $0x0,%ecx
   60014:	ba 00 00 00 00       	mov    $0x0,%edx
   60019:	b9 00 80 00 00       	mov    $0x8000,%ecx
   6001e:	66 bb 01 00          	mov    $0x1,%bx
   60022:	b7 00                	mov    $0x0,%bh
   60024:	c7 05 34 12 00 00 01 	movl   $0x1,0x1234
   6002b:	00 00 00 
   6002e:	a1 34 12 00 00       	mov    0x1234,%eax
   60033:	83 f8 01             	cmp    $0x1,%eax
   60036:	66 c7 05 34 12 00 00 	movw   $0xffff,0x1234
   6003d:	ff ff 
   6003f:	66 a1 34 12 00 00    	mov    0x1234,%ax
   60045:	66 83 f8 ff          	cmp    $0xffff,%ax
   60049:	c6 05 34 12 00 00 01 	movb   $0x1,0x1234
   60050:	c7 01 02 00 00 00    	movl   $0x2,(%ecx)
   60056:	a1 00 80 00 00       	mov    0x8000,%eax
   6005b:	83 f8 02             	cmp    $0x2,%eax
   6005e:	66 c7 01 fe ff       	movw   $0xfffe,(%ecx)
   60063:	66 a1 00 80 00 00    	mov    0x8000,%ax
   60069:	66 83 f8 fe          	cmp    $0xfffe,%ax
   6006d:	c6 01 01             	movb   $0x1,(%ecx)
   60070:	c7 04 99 03 00 00 00 	movl   $0x3,(%ecx,%ebx,4)
   60077:	a1 04 80 00 00       	mov    0x8004,%eax
   6007c:	83 f8 03             	cmp    $0x3,%eax
   6007f:	66 c7 04 99 fd ff    	movw   $0xfffd,(%ecx,%ebx,4)
   60085:	66 a1 04 80 00 00    	mov    0x8004,%ax
   6008b:	66 83 f8 fd          	cmp    $0xfffd,%ax
   6008f:	c6 04 99 01          	movb   $0x1,(%ecx,%ebx,4)
   60093:	c7 41 02 04 00 00 00 	movl   $0x4,0x2(%ecx)
   6009a:	66 a1 02 80 00 00    	mov    0x8002,%ax
   600a0:	66 83 f8 04          	cmp    $0x4,%ax
   600a4:	66 c7 41 02 fc ff    	movw   $0xfffc,0x2(%ecx)
   600aa:	66 a1 02 80 00 00    	mov    0x8002,%ax
   600b0:	66 83 f8 fc          	cmp    $0xfffc,%ax
   600b4:	c6 41 02 01          	movb   $0x1,0x2(%ecx)
   600b8:	c7 41 fe 05 00 00 00 	movl   $0x5,-0x2(%ecx)
   600bf:	a1 fe 7f 00 00       	mov    0x7ffe,%eax
   600c4:	83 f8 05             	cmp    $0x5,%eax
   600c7:	66 c7 41 fe fb ff    	movw   $0xfffb,-0x2(%ecx)
   600cd:	66 a1 fe 7f 00 00    	mov    0x7ffe,%ax
   600d3:	66 83 f8 fb          	cmp    $0xfffb,%ax
   600d7:	c6 41 fe 01          	movb   $0x1,-0x2(%ecx)
   600db:	c7 44 99 02 06 00 00 	movl   $0x6,0x2(%ecx,%ebx,4)
   600e2:	00 
   600e3:	a1 06 80 00 00       	mov    0x8006,%eax
   600e8:	83 f8 06             	cmp    $0x6,%eax
   600eb:	66 c7 44 99 02 fa ff 	movw   $0xfffa,0x2(%ecx,%ebx,4)
   600f2:	66 a1 06 80 00 00    	mov    0x8006,%ax
   600f8:	66 83 f8 fa          	cmp    $0xfffa,%ax
   600fc:	c6 44 99 02 01       	movb   $0x1,0x2(%ecx,%ebx,4)
   60101:	c7 44 99 fe 07 00 00 	movl   $0x7,-0x2(%ecx,%ebx,4)
   60108:	00 
   60109:	a1 02 80 00 00       	mov    0x8002,%eax
   6010e:	83 f8 07             	cmp    $0x7,%eax
   60111:	66 c7 44 99 fe f9 ff 	movw   $0xfff9,-0x2(%ecx,%ebx,4)
   60118:	66 a1 02 80 00 00    	mov    0x8002,%ax
   6011e:	66 83 f8 f9          	cmp    $0xfff9,%ax
   60122:	c6 44 99 fe 01       	movb   $0x1,-0x2(%ecx,%ebx,4)
   60127:	c7 81 00 20 00 00 08 	movl   $0x8,0x2000(%ecx)
   6012e:	00 00 00 
   60131:	a1 00 a0 00 00       	mov    0xa000,%eax
   60136:	83 f8 08             	cmp    $0x8,%eax
   60139:	66 c7 81 00 20 00 00 	movw   $0xfff8,0x2000(%ecx)
   60140:	f8 ff 
   60142:	66 a1 00 a0 00 00    	mov    0xa000,%ax
   60148:	66 83 f8 f8          	cmp    $0xfff8,%ax
   6014c:	c6 81 00 20 00 00 01 	movb   $0x1,0x2000(%ecx)
   60153:	c7 81 00 e0 ff ff 09 	movl   $0x9,-0x2000(%ecx)
   6015a:	00 00 00 
   6015d:	a1 00 60 00 00       	mov    0x6000,%eax
   60162:	83 f8 09             	cmp    $0x9,%eax
   60165:	66 c7 81 00 e0 ff ff 	movw   $0xfff7,-0x2000(%ecx)
   6016c:	f7 ff 
   6016e:	66 a1 00 60 00 00    	mov    0x6000,%ax
   60174:	66 83 f8 f7          	cmp    $0xfff7,%ax
   60178:	c6 81 00 e0 ff ff 01 	movb   $0x1,-0x2000(%ecx)
   6017f:	c7 84 99 00 20 00 00 	movl   $0xa,0x2000(%ecx,%ebx,4)
   60186:	0a 00 00 00 
   6018a:	a1 04 a0 00 00       	mov    0xa004,%eax
   6018f:	83 f8 0a             	cmp    $0xa,%eax
   60192:	66 c7 84 99 00 20 00 	movw   $0xfff6,0x2000(%ecx,%ebx,4)
   60199:	00 f6 ff 
   6019c:	66 a1 04 a0 00 00    	mov    0xa004,%ax
   601a2:	66 83 f8 f6          	cmp    $0xfff6,%ax
   601a6:	c6 84 99 00 20 00 00 	movb   $0x1,0x2000(%ecx,%ebx,4)
   601ad:	01 
   601ae:	c7 84 99 00 e0 ff ff 	movl   $0xb,-0x2000(%ecx,%ebx,4)
   601b5:	0b 00 00 00 
   601b9:	a1 04 60 00 00       	mov    0x6004,%eax
   601be:	83 f8 0b             	cmp    $0xb,%eax
   601c1:	66 c7 84 99 00 e0 ff 	movw   $0xfff5,-0x2000(%ecx,%ebx,4)
   601c8:	ff f5 ff 
   601cb:	66 a1 04 60 00 00    	mov    0x6004,%ax
   601d1:	66 83 f8 f5          	cmp    $0xfff5,%ax
   601d5:	c6 84 99 00 e0 ff ff 	movb   $0x1,-0x2000(%ecx,%ebx,4)
   601dc:	01 
   601dd:	89 c3                	mov    %eax,%ebx
   601df:	66 89 c3             	mov    %ax,%bx
   601e2:	88 e3                	mov    %ah,%bl
   601e4:	a3 34 12 00 00       	mov    %eax,0x1234
   601e9:	66 a3 34 12 00 00    	mov    %ax,0x1234
   601ef:	a2 34 12 00 00       	mov    %al,0x1234
   601f4:	88 25 34 12 00 00    	mov    %ah,0x1234
   601fa:	89 03                	mov    %eax,(%ebx)
   601fc:	89 04 99             	mov    %eax,(%ecx,%ebx,4)
   601ff:	66 89 04 99          	mov    %ax,(%ecx,%ebx,4)
   60203:	88 24 99             	mov    %ah,(%ecx,%ebx,4)
   60206:	89 41 02             	mov    %eax,0x2(%ecx)
   60209:	66 89 41 02          	mov    %ax,0x2(%ecx)
   6020d:	88 61 02             	mov    %ah,0x2(%ecx)
   60210:	89 44 99 02          	mov    %eax,0x2(%ecx,%ebx,4)
   60214:	66 89 44 99 02       	mov    %ax,0x2(%ecx,%ebx,4)
   60219:	88 64 99 02          	mov    %ah,0x2(%ecx,%ebx,4)
   6021d:	89 81 00 20 00 00    	mov    %eax,0x2000(%ecx)
   60223:	66 89 81 00 20 00 00 	mov    %ax,0x2000(%ecx)
   6022a:	88 a1 00 20 00 00    	mov    %ah,0x2000(%ecx)
   60230:	89 84 99 00 20 00 00 	mov    %eax,0x2000(%ecx,%ebx,4)
   60237:	66 89 84 99 00 20 00 	mov    %ax,0x2000(%ecx,%ebx,4)
   6023e:	00 
   6023f:	88 a4 99 00 20 00 00 	mov    %ah,0x2000(%ecx,%ebx,4)
   60246:	89 d3                	mov    %edx,%ebx
   60248:	66 89 d3             	mov    %dx,%bx
   6024b:	88 f3                	mov    %dh,%bl
   6024d:	89 15 34 12 00 00    	mov    %edx,0x1234
   60253:	66 89 15 34 12 00 00 	mov    %dx,0x1234
   6025a:	88 15 34 12 00 00    	mov    %dl,0x1234
   60260:	88 35 34 12 00 00    	mov    %dh,0x1234
   60266:	89 13                	mov    %edx,(%ebx)
   60268:	89 14 99             	mov    %edx,(%ecx,%ebx,4)
   6026b:	66 89 14 99          	mov    %dx,(%ecx,%ebx,4)
   6026f:	88 34 99             	mov    %dh,(%ecx,%ebx,4)
   60272:	89 51 02             	mov    %edx,0x2(%ecx)
   60275:	66 89 51 02          	mov    %dx,0x2(%ecx)
   60279:	88 71 02             	mov    %dh,0x2(%ecx)
   6027c:	89 54 99 02          	mov    %edx,0x2(%ecx,%ebx,4)
   60280:	66 89 54 99 02       	mov    %dx,0x2(%ecx,%ebx,4)
   60285:	88 74 99 02          	mov    %dh,0x2(%ecx,%ebx,4)
   60289:	89 91 00 20 00 00    	mov    %edx,0x2000(%ecx)
   6028f:	66 89 91 00 20 00 00 	mov    %dx,0x2000(%ecx)
   60296:	88 b1 00 20 00 00    	mov    %dh,0x2000(%ecx)
   6029c:	89 94 99 00 20 00 00 	mov    %edx,0x2000(%ecx,%ebx,4)
   602a3:	66 89 94 99 00 20 00 	mov    %dx,0x2000(%ecx,%ebx,4)
   602aa:	00 
   602ab:	88 b4 99 00 20 00 00 	mov    %dh,0x2000(%ecx,%ebx,4)
   602b2:	a1 34 12 00 00       	mov    0x1234,%eax
   602b7:	66 a1 34 12 00 00    	mov    0x1234,%ax
   602bd:	a0 34 12 00 00       	mov    0x1234,%al
   602c2:	8a 25 34 12 00 00    	mov    0x1234,%ah
   602c8:	8b 03                	mov    (%ebx),%eax
   602ca:	8b 04 99             	mov    (%ecx,%ebx,4),%eax
   602cd:	66 8b 04 99          	mov    (%ecx,%ebx,4),%ax
   602d1:	8a 24 99             	mov    (%ecx,%ebx,4),%ah
   602d4:	8b 41 02             	mov    0x2(%ecx),%eax
   602d7:	66 8b 41 02          	mov    0x2(%ecx),%ax
   602db:	8a 61 02             	mov    0x2(%ecx),%ah
   602de:	8b 44 99 02          	mov    0x2(%ecx,%ebx,4),%eax
   602e2:	66 8b 44 99 02       	mov    0x2(%ecx,%ebx,4),%ax
   602e7:	8a 64 99 02          	mov    0x2(%ecx,%ebx,4),%ah
   602eb:	8b 81 00 20 00 00    	mov    0x2000(%ecx),%eax
   602f1:	66 8b 81 00 20 00 00 	mov    0x2000(%ecx),%ax
   602f8:	8a a1 00 20 00 00    	mov    0x2000(%ecx),%ah
   602fe:	8b 84 99 00 20 00 00 	mov    0x2000(%ecx,%ebx,4),%eax
   60305:	66 8b 84 99 00 20 00 	mov    0x2000(%ecx,%ebx,4),%ax
   6030c:	00 
   6030d:	8a a4 99 00 20 00 00 	mov    0x2000(%ecx,%ebx,4),%ah
   60314:	8b 15 34 12 00 00    	mov    0x1234,%edx
   6031a:	66 8b 15 34 12 00 00 	mov    0x1234,%dx
   60321:	8a 15 34 12 00 00    	mov    0x1234,%dl
   60327:	8a 35 34 12 00 00    	mov    0x1234,%dh
   6032d:	8b 13                	mov    (%ebx),%edx
   6032f:	8b 14 99             	mov    (%ecx,%ebx,4),%edx
   60332:	66 8b 14 99          	mov    (%ecx,%ebx,4),%dx
   60336:	8a 34 99             	mov    (%ecx,%ebx,4),%dh
   60339:	8b 51 02             	mov    0x2(%ecx),%edx
   6033c:	66 8b 51 02          	mov    0x2(%ecx),%dx
   60340:	8a 71 02             	mov    0x2(%ecx),%dh
   60343:	8b 54 99 02          	mov    0x2(%ecx,%ebx,4),%edx
   60347:	66 8b 54 99 02       	mov    0x2(%ecx,%ebx,4),%dx
   6034c:	8a 74 99 02          	mov    0x2(%ecx,%ebx,4),%dh
   60350:	8b 91 00 20 00 00    	mov    0x2000(%ecx),%edx
   60356:	66 8b 91 00 20 00 00 	mov    0x2000(%ecx),%dx
   6035d:	8a b1 00 20 00 00    	mov    0x2000(%ecx),%dh
   60363:	8b 94 99 00 20 00 00 	mov    0x2000(%ecx,%ebx,4),%edx
   6036a:	66 8b 94 99 00 20 00 	mov    0x2000(%ecx,%ebx,4),%dx
   60371:	00 
   60372:	8a b4 99 00 20 00 00 	mov    0x2000(%ecx,%ebx,4),%dh
   60379:	b8 00 00 00 00       	mov    $0x0,%eax
   6037e:	82                   	.byte 0x82
