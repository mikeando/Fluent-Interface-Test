import re
import sys

line_splitter = re.compile(r"(\w+)\s+(\w+)\s+(.*)$")
comment = re.compile(r"\s*//.*$")
out_header = re.compile(r"\s*HEADER\s*:\s*(\w+(?:\.h)?(?:\.hpp)?)\s*$")
out_source = re.compile(r"\s*SOURCE\s*:\s*(\w+(?:\.cpp)?(?:\.cxx)?)\s*$")
default_action_re = re.compile(r"\s*DEFAULT_ACTION\s*@([^@]*)@(.*)$")

transition_table = open('transition_table.txt', 'r')

transitions = dict()
structs = set()

header = None
source = None

default_actions ={} # { "SetUrl(std::string url)":"core->SetUrl(url);" }

for l in transition_table:
	l = l.strip()
	l = comment.sub("",l)

	if l!="":
		m=out_header.match(l)
		if m:
			if header!=None:
				print >> sys.stderr, "ERROR: Multiple headers found, %s and %s" % header, m.group(1)
				sys.exit(1)
			header = m.group(1)
			continue
		m=out_source.match(l)
		if m:
			if source!=None:
				print >> sys.stderr, "ERROR: Multiple sources found, %s and %s" % source, m.group(1)
				sys.exit(1)
			source = m.group(1)
			continue
		m = default_action_re.match(l)
		if m:
			default_actions[ m.group(1).strip() ] = m.group(2).strip();
			continue
		m = line_splitter.match(l)
		if not m:
			print >> sys.stderr, "Unable to parse line: %s" % l
		else:
			structs.add(m.group(1))
			structs.add(m.group(2))
			if m.group(1) not in transitions:
				transitions[m.group(1)] = []

			transitions[m.group(1)].append( { 'to':m.group(2), 'fn':m.group(3) } )

print default_actions

hf = open( header, "w" )
sf = open( source, "w" )

print >> hf, "class FluentConfigCore;"
print >> hf, "#include <string>"

for x in structs:
	print >> hf, "class %s;" % x

for x in structs:
	print >> hf, "class %s" % x
	print >> hf, "{"
	print >> hf, "   public:"
	print >> hf, "     explicit %s( FluentConfigCore * in_core ) : core(in_core) {}" % x
	for t in transitions.get(x,[]):
		print >> hf, "    %s %s;" % ( t['to'], t['fn'] )
	print >> hf, "   protected:"
	print >> hf, "     FluentConfigCore * core;"
	print >> hf, "};\n"


print >> sf, "#include \"%s\"" % header
print >> sf, "#include \"FluentConfigCore.h\""
for x in structs:
	for t in transitions.get(x,[]):
		print  >> sf,"%s %s::%s" % (t['to'], x, t['fn'])
		print  >> sf,"{"
		if t['fn'] in default_actions:
			print >> sf,"  "+default_actions[t['fn']]
		print  >> sf,"  return %s(core);" % t['to']
		print  >> sf,"};\n"

