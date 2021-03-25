#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/smalltalk/bin/gst -f

"David Grim
dgrim@ucsc.edu
CSE112"

execname := '$RCSfile: cmdline.st,v $' =~ '.*: (.*),v.*' at: 1.
nl := Character nl.
debug := false.
tables := false.
compress := false.
decompress := false.
argc := 0.

"======LEAF && TREE OBEJCTS====================================="
"Leaf object mostly copied and pasted from example files
 with some additions"
"==============================================================="
Object subclass: Leaf [
   |char count|
    char [ ^ char ]
    count [ ^ count ]

    Leaf class >> new [
       self shouldNotImplement]

    Leaf class >> new: aChar count: aCount [
        |result|
        result := super new.
        result setChar: aChar andCount: aCount.
        ^result]

    setChar: aChar andCount: aCount [
        char := aChar.
        count := aCount.]

    <= other [
        ^ (count < other count)
        | ((count = other count) & (char <= other char))]

    printBase: aStream [
      ^ aStream << self class << '(' << char << ',' << count]

    printOn: aStream [
       (self printBase: aStream) << ')'.]
    
    depthFirst: visitor prefix: string[
       visitor value: char value: string.]

    write: OutFile [
        OutFile writeBit: (0 bitAt: 1).
        OutFile charBit: self char.]]

"Tree object."
Leaf subclass: Tree [
    |left right|
    left [ ^ left ]
    right [ ^ right ]

    Tree class >> new: aChar count: aCount [
        self shouldNotImplement]

    Tree class >> new: aChar count: aCount left: aLeft right: aRight [
      |result|
      result := super new: aChar count: aCount.
      result setLeft: aLeft andRight: aRight.
      ^ result]

    setLeft: aLeft andRight: aRight [
        left := aLeft.
        right := aRight.]

    printOn: aStream [
       (self printBase: aStream) << ',' << left << ',' << right << ')'.]

    depthFirst: visitor prefix: string [
       left depthFirst: visitor prefix: string, '0'.
       right depthFirst: visitor prefix: string, '1'.]

    write: OutFile [
        left write: OutFile.
        right write: OutFile.
        OutFile writeBit: (1 bitAt: 1).]]

"==============ZeroArray Object================================="
"ZeroArray object. Simply a copy and paste from the example files. 
Nothing new"
"==============================================================="
Object subclass: ZeroArray [
    |theArray|

    ZeroArray class >> new [
      self shouldNotImplement.]

    ZeroArray class >> new: size [
        |result|
        result := super new.
        result init: size.
        ^ result]

    init: size [
      theArray := Array new: size.]

    size [
      ^ theArray size.]

    at: index [
       ^ theArray at: index + 1.]

    at: index put: value [
      ^ theArray at: index + 1 put: value.]

    incr: index [
        (self at: index) isNil
         ifTrue: [ self at: index put: 0].
         self at: index put: (self at: index) + 1.]

    keysAndValuesDo: aBlock [
        (0 to: (self size) - 1) do: [:index |
           aBlock value: index value: (self at: index).]]]

"============Extension of Char class============================"
"Extension of Character, based from bitstream.st"
"==============================================================="
Character extend [
    isGraph [
       ^(Character space < self) & (self <= $~)]

    asBit [
       ^ self value bitAt: 1.]

    isPrint [
       ^ ($! <= self) & (self <= $~)]

    digits[
         ^ (self asInteger) > 15]

    visible [
      self isGraph
      ifTrue: [^ '$', self asString]
      ifFalse: [^ self asInteger printStringRadix: 16].

      self isPrint 
      ifTrue: [^' ', self asString, ' ']             
      ifFalse: [ self digits
             ifTrue:[((self asInteger) = 256)
                    ifTrue:[ ^ 'EOF']ifFalse:[^ 'x',
                   ((self asInteger printStringRadix: 16)
                   copyFrom: 4 )]
                             ]
             ifFalse:[  ^ 'x0',
                        ((self asInteger printStringRadix: 16)
                         copyFrom: 4)]]]]

"==========Bitstream object===================================="
"BitStream object based on bitstream.st"
"==============================================================="
Object subclass: BitStream [
    |bitIndex currentByte myStream|

    BitStream class >> new: fileStream [
      |result|
      result := super new.
      result init: fileStream.
      ^result]
   init: fileStream [
      myStream := fileStream.]
  
   flushByte [
        bitIndex = 8 ifFalse: [
           myStream nextPut: (Character value: currentByte asInteger).
            bitIndex := 8.
            currentByte := 0.]]

    writeBit: bit [
        currentByte isNil ifTrue: 
        [bitIndex := 8. currentByte := 0.].
        bitIndex = 0 ifTrue: [self flushByte].
        currentByte := currentByte bitAt: bitIndex put: bit.
        bitIndex := bitIndex - 1.]

    clearBits [
       bitIndex := 0.]

    nextBit [
        |bit|
        bitIndex isNil ifTrue: [self clearBits].
        bitIndex = 0 ifTrue: 
        [currentByte := myStream next. bitIndex := 8.].
        currentByte isNil ifTrue: [ ^ nil ].
        bit := currentByte value bitAt: bitIndex.
        bitIndex := bitIndex - 1.
        ^ bit.]

    charBit: char [
        |bit charVal bitIndex|
        charVal := char value.
        bitIndex := 8.
        [bitIndex ~= 0] whileTrue: [
            bit := char value bitAt: bitIndex.
            bitIndex := bitIndex - 1.
            self writeBit: bit.
        ].
        (charVal = 0) | (charVal = 256) ifTrue: [
            self writeBit: (charVal bitAt: 9).].]]
"========================================================="            
"==========Args================================================="
Smalltalk arguments: '-a -b -c -u'
do: [:opt :arg |
   (opt = $a) ifTrue: [ debug := true.].
   (opt = $b) ifTrue: [ tables := true.].
   (opt = $c) ifTrue: [ compress := true.].
   (opt = $u) ifTrue: [ decompress := true.].].
   
"Set the InFile and OutFile args"
InFileName := (Smalltalk getArgv: 2).
OutFileName := (Smalltalk getArgv: 3).

"Check to see the number of args is less than 2"
Smalltalk arguments size < 2
ifTrue: [ 
    stderr << 'Input error:' << execname 
    << ' -dtcu inputfile [outputfile]' << nl.
    ObjectMemory quit.].
"================================================================"

"==========Create Freq Table====================================="
"Use the frequency table created earlier to count the frequency
of chars"
freqtable := ZeroArray new: 260.
        |InFile char|
        [InFile := FileStream open: InFileName
            mode: FileStream read.
            [InFile atEnd] whileFalse: [
            char := InFile next asInteger.
            freqtable incr: char.].
          char = nil ifFalse: [
            freqtable incr: 256.].
          InFile close.] 
        on: SystemExceptions.FileError do: [:signal |
        |err|
        err := File err.
        stdout flush.
        stderr << execname << ': ' << OutFileName << ': '
               << signal messageText << nl.
        stderr flush.].
"==============================================================="

"====load priority queue from frequency table==================="
    priorityQueue := SortedCollection new.
    freqtable keysAndValuesDo: [:key :count |
        (count notNil and: [count > 0]) ifTrue: [
            priorityQueue add:(Leaf new: (key asCharacter) 
            count: count).]].
"==============================================================="

"=======unload onto the huffman tree============================"
    [priorityQueue notEmpty] whileTrue: [
        tree := priorityQueue removeFirst.
        priorityQueue size = 0 ifTrue: [^ tree].
        right := priorityQueue removeFirst.
        priorityQueue add: (Tree new: tree char 
        count: (tree count + right count)
        left: tree right: right).].
"==============================================================="

"===========transfer tree contents into array==================="
    enCharArray := ZeroArray new: 257.
    tree = nil ifFalse: [
        tree depthFirst: [:char :encoding |
            enCharArray at: char asInteger put: encoding.] 
            prefix: ''.].
"==============================================================="

"======================Debugging actions========================"
debug ifTrue: [
     priorityQueue inspect.
     stdout << tree << nl.].
"==============================================================="

"==================Print tables================================="
tables ifTrue: [
    freqtable keysAndValuesDo: [:key :value |
        (value notNil and: [value > 0]) ifTrue: [
             |character|
             character := (key asCharacter visible).
             character asString size to: 3 do: [:skip| stdout].
             stdout << character << ' '. 
             value asString size to: 6 do: [:skip| stdout << ' '].
             stdout << value << '  '.
             stdout << (enCharArray at: key) << nl.]]].
"==============================================================="
"=====Compression of the input file into the output file========"
compress ifTrue: [
    [|InFile OutFile enChar OutputBit|
      InFile := FileStream open: InFileName
         mode: FileStream read.
        OutFileName = nil
        ifTrue: [
           OutFile := stdout.]
        ifFalse: [
            OutFile := FileStream open: OutFileName
                mode: FileStream write.].
        OutputBit := BitStream new: OutFile.
        tree = nil ifFalse: [
            tree write: OutputBit.
            OutputBit writeBit: (1 bitAt: 1).
            OutputBit flushByte.
        [InFile atEnd not] whileTrue: [
            enChar := 
            enCharArray at: InFile next value.
            enChar do: [:char |
            OutputBit writeBit: char asBit.].].
        enChar := enCharArray at: 256.
        enChar do: [:char |
           OutputBit writeBit: char asBit.].
        OutputBit flushByte.].
        OutFile close.
        InFile close.] 
        on: SystemExceptions.FileError do: [:signal |
        |err|
        err := File err.
        stdout flush.
        stderr << execname << ': ' << OutFileName << ': '
               << signal messageText << nl.
        stderr flush.].].
"==============================================================="

"=====Decompression of the input file into the output file======"
decompress ifTrue: [
    [|bit Tree1 InFile OutFile stack inputBits bl|
        InFile := FileStream open: InFileName
           mode: FileStream read.
        inputBits := BitStream new: InFile.
        stack := OrderedCollection new.
        bl:= true.
        [(InFile atEnd not) & (bl == true)] whileTrue: [
            |preBit|
            preBit := inputBits nextBit.
            preBit = 0 ifTrue: [
                |bit charBit bitIndex newLeaf|
                charBit := 0.
                bitIndex := 8.
                [bitIndex ~= 0] whileTrue: [
                   charBit := 
                   charBit bitAt: bitIndex put: inputBits nextBit.
                   bitIndex := bitIndex - 1.].
                newLeaf := Leaf new: (charBit asCharacter) count: 0.
                charBit = 0 ifTrue: [
                    bit := inputBits nextBit.
                    bit = 1 ifTrue: [
                       newLeaf := Leaf new: 256 count: 0.].].
            stack addFirst: newLeaf.].
            preBit = 1 ifTrue: [
                |leftChild right newTree|
                right := stack removeFirst.
                stack size = 0 ifTrue: [
                inputBits clearBits.
                stack addFirst: right.
                    bl := false.].
                bl ifTrue: [leftChild := stack removeFirst.
                newTree := Tree new: leftChild char 
                count: 0 left: leftChild right: right.
                stack addFirst: newTree.].].].
        (stack size ~= 0) ifTrue:[tree := stack removeFirst].
        tree = nil ifFalse: [
            OutFileName = nil
            ifTrue: [
               OutFile := stdout.]
            ifFalse: [
            OutFile := FileStream open: OutFileName
                    mode: FileStream write.].
        Tree1 := tree.
        bit := 0.
       [bit ~= nil] whileTrue: [
            bit := inputBits nextBit.
            bit = 0 ifTrue: [
               Tree1 := Tree1 left.].
            bit = 1 ifTrue: [
               Tree1 := Tree1 right.].
            (Tree1 isMemberOf: Leaf) ifTrue: [
                |char|
                Tree1 char = 256 ifTrue: [ ^ char ].
                char := Character value: Tree1 char asInteger.
                OutFile nextPut: char.
                Tree1 := tree.].].
        OutFile close.].
        InFile close.]
     on: SystemExceptions.FileError do: [:signal |
        |err|
        err := File err.
        stdout flush.
        stderr << execname << ': ' << OutFileName << ': '
               << signal messageText << nl.
        stderr flush.].].
"==============================================================="
