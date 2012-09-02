#!/bin/bash
cat <<\EOL > script.sh
#!/bin/bash
echo Hello World
for i in H e l l o W o r l d; do
  echo $i
done
EOL
