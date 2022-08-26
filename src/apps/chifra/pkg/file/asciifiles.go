// Copyright 2021 The TrueBlocks Authors. All rights reserved.
// Use of this source code is governed by a license that can
// be found in the LICENSE file.

package file

import (
	"bufio"
	"io"
	"log"
	"os"
	"strings"
)

func AsciiFileToLines(filename string) []string {
	file, err := os.Open(filename)
	if err != nil {
		return []string{}
	}
	scanner := bufio.NewScanner(file)
	scanner.Split(bufio.ScanLines)
	var ret []string
	for scanner.Scan() {
		ret = append(ret, scanner.Text())
	}
	file.Close()
	return ret
}

func AsciiFileToString(fileName string) string {
	if !FileExists(fileName) {
		return ""
	}

	contents, err := os.ReadFile(fileName)
	if err != nil {
		log.Println(err)
		return ""
	}

	return string(contents)
}

func StringToAsciiFile(filename, value string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	_, err = io.WriteString(file, value)
	if err != nil {
		return err
	}
	return file.Sync()
}

func AppendToAsciiFile(filename, value string) error {
	// TODO: BOGUS - WORK - Protect against failure while writing
	file, err := os.OpenFile(filename, os.O_WRONLY|os.O_CREATE|os.O_APPEND, 0644)
	if err != nil {
		return err
	}
	defer file.Close()
	if _, err := file.Write([]byte(value)); err != nil {
		return err
	}
	return file.Sync()
}

func LinesToAsciiFile(filename string, value []string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	lines := strings.Join(value, "\n") + "\n"
	_, err = io.WriteString(file, lines)
	if err != nil {
		return err
	}

	return file.Sync()
}
