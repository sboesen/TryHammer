/usr/sbin/atd &
echo "poweroff" | at now + 30 minutes
node /node_modules/codebox/bin/codebox.js -e hammer@hammer.hammer run /hammer_examples
