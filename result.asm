.data
string0: .ascii "not H"
string5: .ascii "b is not bigger than c[5]\n"
string1: .ascii "next period\n"
f: .space 80
string4: .ascii "b is bigger than c[5]\n"
a: .space 40
newLine: .ascii "\n"


.text
faaaaaab:
move $fp,$sp
addi $sp,$sp,-64

lw $t3,12($sp)
add $t1,$0,$t3
sw $t1,20($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,16($sp)

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,12($sp)

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,24($sp)

lw $t3,24($sp)
add $t1,$0,$t3
sw $t1,20($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,16($sp)

lw $t1,12($sp)
lw $t2,16($sp)
bgez $t1,$t2,aaab
nop

j aaab
nop

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,28($sp)

lw $t3,28($sp)
add $t1,$0,$t3
sw $t1,24($sp)

lw $t3,24($sp)
add $t1,$0,$t3
sw $t1,20($sp)

move $vo,20
jr $ra
nop

aaab:

lw $t3,12($sp)
add $t1,$0,$t3
sw $t1,32($sp)

lw $t3,32($sp)
add $t1,$0,$t3
sw $t1,28($sp)

lw $t3,28($sp)
add $t1,$0,$t3
sw $t1,24($sp)

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,36($sp)

lw $t3,36($sp)
add $t1,$0,$t3
sw $t1,32($sp)

adi $t1,$0,100
sw $t1,40($sp)

lw $t2,32($sp)
lw $t3,40($sp)
div $t1,$t2,$t3
mflo 32

adi $t1,$0,1
sw $t1,44($sp)

lw $t2,32($sp)
lw $t3,44($sp)
mult $t1,$t2,$t3
mflo 32

lw $t3,32($sp)
add $t1,$0,$t3
sw $t1,28($sp)

lw $t1,24($sp)
lw $t2,28($sp)
blez $t1,$t2,baab
nop

j baab
nop

lw $t3,12($sp)
add $t1,$0,$t3
sw $t1,56($sp)

lw $t3,56($sp)
add $t1,$0,$t3
sw $t1,52($sp)

adi $t1,$0,100
sw $t1,60($sp)

lw $t2,52($sp)
lw $t3,60($sp)
mult $t1,$t2,$t3
mflo 52

lw $t3,52($sp)
add $t1,$0,$t3
sw $t1,48($sp)

lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,40($sp)

lw $t3,40($sp)
add $t1,$0,$t3
sw $t1,36($sp)

lw $t3,36($sp)
add $t1,$0,$t3
sw $t1,32($sp)

move $vo,32
jr $ra
nop

baab:

lw $t3,12($sp)
add $t1,$0,$t3
sw $t1,60($sp)

lw $t3,60($sp)
add $t1,$0,$t3
sw $t1,56($sp)

adi $t1,$0,10
sw $t1,64($sp)

lw $t2,56($sp)
lw $t3,64($sp)
mult $t1,$t2,$t3
mflo 56

lw $t3,56($sp)
add $t1,$0,$t3
sw $t1,52($sp)

lw $t3,48($sp)
add $t1,$0,$t3
sw $t1,44($sp)

lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,40($sp)

lw $t3,40($sp)
add $t1,$0,$t3
sw $t1,36($sp)

move $vo,36
jr $ra
nop

adi $t1,$0,0
sw $t1,48($sp)

lw $t3,48($sp)
add $t1,$0,$t3
sw $t1,44($sp)

lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,40($sp)

move $vo,40
jr $ra
nop

haaaaaab:
move $fp,$sp
addi $sp,$sp,-24

lw $t3,24($sp)
add $t1,$0,$t3
sw $t1,16($sp)

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,12($sp)

lw $t3,12($sp)
add $t1,$0,$t3
sw $t1,8($sp)

lw $t3,-39999712($sp)
add $t1,$0,$t3
sw $t1,20($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,16($sp)

lw $t3,16($sp)
add $t1,$0,$t3
sw $t1,12($sp)

lw $t1,8($sp)
lw $t2,12($sp)
beq $t1,$t2,caab
nop

j caab
nop

lw $t3,24($sp)
add $t1,$0,$t3
sw $t1,24($sp)

lw $t3,24($sp)
add $t1,$0,$t3
sw $t1,20($sp)

lw $t3,20($sp)
add $t1,$0,$t3
sw $t1,16($sp)

caab:

jaaaaaab:
move $fp,$sp
addi $sp,$sp,-188

adi $t1,$0,0
sw $t1,92($sp)

lw $t3,92($sp)
add $t1,$0,$t3
sw $t1,88($sp)

lw $t3,88($sp)
add $t1,$0,$t3
sw $t1,84($sp)

lw $t3,84($sp)
add $t1,$0,$t3
sw $t1,56($sp)

daab:

lw $t3,56($sp)
add $t1,$0,$t3
sw $t1,96($sp)

lw $t3,96($sp)
add $t1,$0,$t3
sw $t1,92($sp)

lw $t3,92($sp)
add $t1,$0,$t3
sw $t1,88($sp)

lw $t3,0($sp)
add $t1,$0,$t3
sw $t1,100($sp)

lw $t3,100($sp)
add $t1,$0,$t3
sw $t1,96($sp)

lw $t3,96($sp)
add $t1,$0,$t3
sw $t1,92($sp)

lw $t1,88($sp)
lw $t2,92($sp)
bltz $t1,$t2,daab
nop

lw $t3,56($sp)
add $t1,$0,$t3
sw $t1,104($sp)

lw $t3,104($sp)
add $t1,$0,$t3
sw $t1,100($sp)

lw $t3,100($sp)
add $t1,$0,$t3
sw $t1,96($sp)

lw $t3,52($sp)
add $t1,$0,$t3
sw $t1,112($sp)

lw $t3,112($sp)
add $t1,$0,$t3
sw $t1,108($sp)

lw $t3,108($sp)
add $t1,$0,$t3
sw $t1,104($sp)

lw $t3,104($sp)
add $t1,$0,$t3
sw $t1,100($sp)

lw $t2,56($sp)
adi $t1,$t2,1
sw $t1,56($sp)

j daab
nop

eaab:

adi $t1,$0,0
sw $t1,116($sp)

lw $t3,116($sp)
add $t1,$0,$t3
sw $t1,112($sp)

lw $t3,112($sp)
add $t1,$0,$t3
sw $t1,108($sp)

lw $t3,108($sp)
add $t1,$0,$t3
sw $t1,56($sp)

adi $t1,$0,0
sw $t1,120($sp)

lw $t3,120($sp)
add $t1,$0,$t3
sw $t1,116($sp)

lw $t3,116($sp)
add $t1,$0,$t3
sw $t1,112($sp)

lw $t3,112($sp)
add $t1,$0,$t3
sw $t1,56($sp)

faab:

lw $t3,56($sp)
add $t1,$0,$t3
sw $t1,124($sp)

lw $t3,124($sp)
add $t1,$0,$t3
sw $t1,120($sp)

lw $t3,120($sp)
add $t1,$0,$t3
sw $t1,116($sp)

lw $t3,0($sp)
add $t1,$0,$t3
sw $t1,128($sp)

lw $t3,128($sp)
add $t1,$0,$t3
sw $t1,124($sp)

lw $t3,124($sp)
add $t1,$0,$t3
sw $t1,120($sp)

lw $t1,116($sp)
lw $t2,120($sp)
bltz $t1,$t2,faab
nop

lw $t3,64($sp)
add $t1,$0,$t3
sw $t1,132($sp)

lw $t3,132($sp)
add $t1,$0,$t3
sw $t1,128($sp)

lw $t3,128($sp)
add $t1,$0,$t3
sw $t1,124($sp)

lw $t2,56($sp)
adi $t1,$t2,1
sw $t1,56($sp)

j faab
nop

gaab:

adi $t1,$0,100
sw $t1,152($sp)

lw $t3,152($sp)
add $t1,$0,$t3
sw $t1,148($sp)

lw $t3,148($sp)
add $t1,$0,$t3
sw $t1,144($sp)

lw $t3,4($sp)
add $t1,$0,$t3
sw $t1,156($sp)

lw $t3,156($sp)
add $t1,$0,$t3
sw $t1,152($sp)

lw $t3,152($sp)
add $t1,$0,$t3
sw $t1,148($sp)

lw $t3,140($sp)
add $t1,$0,$t3
sw $t1,136($sp)

lw $t3,136($sp)
add $t1,$0,$t3
sw $t1,132($sp)

adi $t1,$0,11
sw $t1,140($sp)

lw $t2,132($sp)
lw $t3,140($sp)
mult $t1,$t2,$t3
mflo 132

lw $t3,132($sp)
add $t1,$0,$t3
sw $t1,128($sp)

adi $t1,$0,10
sw $t1,140($sp)

lw $t3,140($sp)
add $t1,$0,$t3
sw $t1,136($sp)

lw $t3,136($sp)
add $t1,$0,$t3
sw $t1,132($sp)

lw $t3,132($sp)
add $t1,$0,$t3
sw $t1,44($sp)

adi $t1,$0,5
sw $t1,144($sp)

lw $t3,144($sp)
add $t1,$0,$t3
sw $t1,140($sp)

lw $t3,140($sp)
add $t1,$0,$t3
sw $t1,136($sp)

adi $t1,$0,7
sw $t1,152($sp)

lw $t3,152($sp)
add $t1,$0,$t3
sw $t1,148($sp)

lw $t3,148($sp)
add $t1,$0,$t3
sw $t1,144($sp)

lw $t3,144($sp)
add $t1,$0,$t3
sw $t1,140($sp)

lw $t3,44($sp)
add $t1,$0,$t3
sw $t1,156($sp)

lw $t3,156($sp)
add $t1,$0,$t3
sw $t1,152($sp)

lw $t3,152($sp)
add $t1,$0,$t3
sw $t1,148($sp)

adi $t1,$0,5
sw $t1,176($sp)

lw $t3,176($sp)
add $t1,$0,$t3
sw $t1,172($sp)

lw $t3,172($sp)
add $t1,$0,$t3
sw $t1,168($sp)

lw $t3,172($sp)
add $t1,$0,$t3
sw $t1,160($sp)

lw $t3,160($sp)
add $t1,$0,$t3
sw $t1,156($sp)

lw $t3,156($sp)
add $t1,$0,$t3
sw $t1,152($sp)

lw $t1,148($sp)
lw $t2,152($sp)
bgtz $t1,$t2,haab
nop

j haab
nop

haab:

adi $t1,$0,1
sw $t1,180($sp)

lw $t3,180($sp)
add $t1,$0,$t3
sw $t1,176($sp)

lw $t3,176($sp)
add $t1,$0,$t3
sw $t1,172($sp)

adi $t1,$0,2
sw $t1,184($sp)

lw $t3,184($sp)
add $t1,$0,$t3
sw $t1,180($sp)

adi $t1,$0,3
sw $t1,188($sp)

lw $t2,180($sp)
lw $t3,188($sp)
mult $t1,$t2,$t3
mflo 180

lw $t2,172($sp)
lw $t3,180($sp)
add $t1,$t2,$t3
sw $t1,172($sp)

lw $t3,172($sp)
add $t1,$0,$t3
sw $t1,164($sp)

lw $t3,164($sp)
add $t1,$0,$t3
sw $t1,160($sp)

adi $t1,$0,111
sw $t1,168($sp)

lw $t2,160($sp)
lw $t3,168($sp)
mult $t1,$t2,$t3
mflo 160

lw $t3,160($sp)
add $t1,$0,$t3
sw $t1,156($sp)
