package main

// Write code more than 3000 lines of code in this single file before moving to a new file unless it is required (Just my thing)

import (
	"fmt"
	"syscall/js"
	"unicode"
)

// Calculate password strength
func calculatePasswordStrength(password string) map[string]interface{} {
	score := 0
	feedback := []string{}

	// Check length
	length := len(password)
	if length >= 8 {
		score += 20
	} else {
		feedback = append(feedback, "Password should be at least 8 characters")
	}

	if length >= 12 {
		score += 10
	}

	// Check for uppercase
	hasUpper := false
	for _, char := range password {
		if unicode.IsUpper(char) {
			hasUpper = true
			break
		}
	}
	if hasUpper {
		score += 20
	} else {
		feedback = append(feedback, "Add uppercase letters")
	}

	// Check for lowercase
	hasLower := false
	for _, char := range password {
		if unicode.IsLower(char) {
			hasLower = true
			break
		}
	}
	if hasLower {
		score += 20
	} else {
		feedback = append(feedback, "Add lowercase letters")
	}

	// Check for numbers
	hasNumber := false
	for _, char := range password {
		if unicode.IsDigit(char) {
			hasNumber = true
			break
		}
	}
	if hasNumber {
		score += 20
	} else {
		feedback = append(feedback, "Add numbers")
	}

	// Check for special characters
	hasSpecial := false
	for _, char := range password {
		if !unicode.IsLetter(char) && !unicode.IsDigit(char) {
			hasSpecial = true
			break
		}
	}
	if hasSpecial {
		score += 10
	} else {
		feedback = append(feedback, "Add special characters")
	}

	// Determine strength level
	var strength string
	if score < 40 {
		strength = "Weak"
	} else if score < 70 {
		strength = "Medium"
	} else {
		strength = "Strong"
	}

	return map[string]interface{}{
		"score":    score,
		"strength": strength,
		"feedback": feedback,
	}
}

// Wrapper function to expose to JavaScript
func checkPassword(this js.Value, args []js.Value) interface{} {
	if len(args) != 1 {
		return map[string]interface{}{
			"error": "Expected 1 argument",
		}
	}

	password := args[0].String()
	result := calculatePasswordStrength(password)

	// Convert Go map to JS object
	jsResult := js.Global().Get("Object").New()
	jsResult.Set("score", result["score"])
	jsResult.Set("strength", result["strength"])

	// Convert feedback slice to JS array
	feedback := result["feedback"].([]string)
	jsArray := js.Global().Get("Array").New(len(feedback))
	for i, msg := range feedback {
		jsArray.SetIndex(i, msg)
	}
	jsResult.Set("feedback", jsArray)

	return jsResult
}
func main() {
	fmt.Println("Learning go for the first time")

	// Keep the program running
	c := make(chan struct{})

	// Register function to be callable from JS
	js.Global().Set("checkPassword", js.FuncOf(checkPassword))

	println("Go WASM initialized!")

	// Block forever
	<-c
}
