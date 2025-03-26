# 🔍 Boolean Information Retrieval System

A lightweight and efficient Boolean Information Retrieval (IR) engine built in C++. This project demonstrates the core principles of classical IR by indexing a collection of documents and enabling Boolean query processing using `AND`, `OR`, and `NOT` operations.

---

## 📚 Features

- Document preprocessing (tokenization, normalization, optional stopword removal)
- Term-document incidence matrix construction
- Inverted index generation
- Support for Boolean queries with:
  - `AND` (intersection)
  - `OR` (union)
  - `NOT` (complement)
- Fast set operations using standard data structures
- Clean and modular C++ code

---

## 🧠 How It Works

1. **Preprocess Documents**  
   Each document is tokenized and normalized into terms. Optionally, stopwords are removed.

2. **Build Inverted Index**  
   An inverted index is created that maps each term to a list of document IDs in which it appears.

3. **Boolean Query Evaluation**  
   The user enters a Boolean query like:
   ```
   lamborghini AND ferrari NOT porsche
   ```
   The system parses the query and retrieves matching documents using set operations on the inverted index.

---

## Run

```bash
./bin/boolean_ir
```

---

## 🧪 Example

**Documents:**

```
[0] Lamborghini is a racing game.
[1] Ferrari is a classic car brand.
[2] Porsche makes performance vehicles.
```

**Query:**

```
lamborghini AND racing NOT porsche
```

**Result:**

```
Matched Document IDs: [0]
```

---

## 📄 License

This project is open-source under the [MIT License](LICENSE).

---

## 👨‍💻 Author

Built with ❤️ by Maxennce Labourel
Feel free to fork, star, and contribute!

---
